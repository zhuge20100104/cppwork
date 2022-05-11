#include "arr_/arr_.h"

#include <iostream>

arrow::Status ArrowUtil::read_csv(char const* file_name,
                                  std::shared_ptr<arrow::Table>& tb) {
    auto fs = std::make_shared<arrow::fs::LocalFileSystem>();

    ARROW_ASSIGN_OR_RAISE(auto info, fs->GetFileInfo(file_name));

    auto format = std::make_shared<arrow::dataset::CsvFileFormat>();
    ARROW_ASSIGN_OR_RAISE(
        auto factory,
        arrow::dataset::FileSystemDatasetFactory::Make(
            fs, {info}, format, arrow::dataset::FileSystemFactoryOptions()));
    ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());
    tb = table;
    return arrow::Status::OK();
}

arrow::Status ArrowUtil::read_ipc(char const* file_name,
                                  std::shared_ptr<arrow::Table>& tb) {
    auto fs = std::make_shared<arrow::fs::LocalFileSystem>();

    ARROW_ASSIGN_OR_RAISE(auto info, fs->GetFileInfo(file_name));

    auto format = std::make_shared<arrow::dataset::IpcFileFormat>();
    ARROW_ASSIGN_OR_RAISE(
        auto factory,
        arrow::dataset::FileSystemDatasetFactory::Make(
            fs, {info}, format, arrow::dataset::FileSystemFactoryOptions()));
    ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());
    tb = table;
    return arrow::Status::OK();
}

arrow::Status ArrowUtil::read_parquet(char const* file_name,
                                      std::shared_ptr<arrow::Table>& tb) {
    auto fs = std::make_shared<arrow::fs::LocalFileSystem>();

    ARROW_ASSIGN_OR_RAISE(auto info, fs->GetFileInfo(file_name));

    auto format = std::make_shared<arrow::dataset::ParquetFileFormat>();
    ARROW_ASSIGN_OR_RAISE(
        auto factory,
        arrow::dataset::FileSystemDatasetFactory::Make(
            fs, {info}, format, arrow::dataset::FileSystemFactoryOptions()));
    ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());
    tb = table;
    return arrow::Status::OK();
}

arrow::Status ArrowUtil::read_json(char const* file_name,
                                   std::shared_ptr<arrow::Table>& tb) {
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(
        infile,
        arrow::io::ReadableFile::Open(file_name, arrow::default_memory_pool()));

    ARROW_ASSIGN_OR_RAISE(
        auto reader,
        arrow::json::TableReader::Make(arrow::default_memory_pool(), infile,
                                       arrow::json::ReadOptions::Defaults(),
                                       arrow::json::ParseOptions::Defaults()));

    ARROW_ASSIGN_OR_RAISE(auto res_tb, reader->Read());
    tb = res_tb;
    return arrow::Status::OK();
}

arrow::Status ArrowUtil::write_ipc(arrow::Table const& tb,
                                   char const* file_name) {
    auto fs = std::make_shared<arrow::fs::LocalFileSystem>();
    ARROW_ASSIGN_OR_RAISE(auto output_file, fs->OpenOutputStream(file_name));
    ARROW_ASSIGN_OR_RAISE(auto batch_writer,
                          arrow::ipc::MakeFileWriter(output_file, tb.schema()));
    ARROW_RETURN_NOT_OK(batch_writer->WriteTable(tb));
    ARROW_RETURN_NOT_OK(batch_writer->Close());

    return arrow::Status::OK();
}

arrow::Status ArrowUtil::write_parquet(arrow::Table const& tb,
                                       char const* file_name) {
    auto fs = std::make_shared<arrow::fs::LocalFileSystem>();
    PARQUET_ASSIGN_OR_THROW(auto outfile, fs->OpenOutputStream(file_name));
    // The last argument to the function call is the size of the RowGroup in
    // the parquet file. Normally you would choose this to be rather large but
    // for the example, we use a small value to have multiple RowGroups.
    PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(
        tb, arrow::default_memory_pool(), outfile, 2048));
    return arrow::Status::OK();
}

arrow::Result<arrow::compute::ExecNode*> ArrowUtil::MakeTestSourceNode(
    arrow::compute::ExecPlan* plan, std::string label,
    BatchesWithSchema batches_with_schema, bool parallel, bool slow) {
    DCHECK_GT(batches_with_schema.batches.size(), 0);

    auto opt_batches = ::arrow::internal::MapVector(
        [](arrow::compute::ExecBatch batch) {
            return arrow::util::make_optional(std::move(batch));
        },
        std::move(batches_with_schema.batches));

    arrow::AsyncGenerator<arrow::util::optional<arrow::compute::ExecBatch>> gen;

    if (parallel) {
        // emulate batches completing initial decode-after-scan on a cpu thread
        ARROW_ASSIGN_OR_RAISE(
            gen, MakeBackgroundGenerator(
                     arrow::MakeVectorIterator(std::move(opt_batches)),
                     ::arrow::internal::GetCpuThreadPool()));

        // ensure that callbacks are not executed immediately on a background
        // thread
        gen = MakeTransferredGenerator(std::move(gen),
                                       ::arrow::internal::GetCpuThreadPool());
    } else {
        gen = arrow::MakeVectorGenerator(std::move(opt_batches));
    }

    if (slow) {
        gen = arrow::MakeMappedGenerator(
            std::move(gen),
            [](const arrow::util::optional<arrow::compute::ExecBatch>& batch) {
                ArrowUtil::SleepFor(1e-3);
                return batch;
            });
    }

    return arrow::compute::MakeSourceNode(
        plan, label, std::move(batches_with_schema.schema), std::move(gen));
}

arrow::Future<std::vector<arrow::compute::ExecBatch>>
ArrowUtil::StartAndCollect(
    arrow::compute::ExecPlan* plan,
    arrow::AsyncGenerator<arrow::util::optional<arrow::compute::ExecBatch>>
        gen) {
    RETURN_NOT_OK(plan->Validate());
    RETURN_NOT_OK(plan->StartProducing());

    auto collected_fut = CollectAsyncGenerator(gen);

    return arrow::AllComplete(
               {plan->finished(), arrow::Future<>(collected_fut)})
        .Then([collected_fut]()
                  -> arrow::Result<std::vector<arrow::compute::ExecBatch>> {
            ARROW_ASSIGN_OR_RAISE(auto collected, collected_fut.result());
            return ::arrow::internal::MapVector(
                [](arrow::util::optional<arrow::compute::ExecBatch> batch) {
                    return std::move(*batch);
                },
                std::move(collected));
        });
}

BatchesWithSchema ArrowUtil::MakeBatchAndSchema(
    std::shared_ptr<arrow::Table> const& tb) {
    arrow::TableBatchReader reader(*tb);
    auto schema = tb->schema();

    std::vector<arrow::compute::ExecBatch> ex_batches;
    std::shared_ptr<arrow::RecordBatch> a_batch;
    while (reader.ReadNext(&a_batch).ok()) {
        if (nullptr == a_batch) {
            break;
        }
        arrow::compute::ExecBatch batch(*a_batch);
        ex_batches.emplace_back(std::move(batch));
    }

    BatchesWithSchema batche_sh{ex_batches, schema};
    return batche_sh;
}

arrow::Status ArrowUtil::ConvertExecBatchToRecBatch(
    std::shared_ptr<arrow::Schema> const& schema,
    std::vector<arrow::compute::ExecBatch> const& exec_batches,
    arrow::RecordBatchVector& out_rec_batches) {
    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    for (auto ex_batch : exec_batches) {
        rec_batches.emplace_back(
            ex_batch.ToRecordBatch(schema, arrow::default_memory_pool())
                .ValueOrDie());
    }
    out_rec_batches = std::move(rec_batches);
    return arrow::Status::OK();
}

std::shared_ptr<arrow::Array> ArrowUtil::ArrayFromJSON(const std::shared_ptr<arrow::DataType>& type, std::string const& json) {
    std::shared_ptr<arrow::Array> out;
    ABORT_NOT_OK(arrow::ipc::internal::json::ArrayFromJSON(type, json, &out));
    return out;
}

std::shared_ptr<arrow::RecordBatch> ArrowUtil::RecordBatchFromJSON(
    const std::shared_ptr<arrow::Schema>& schema, std::string const& json) {
    // Parse as a StructArray
    auto struct_type = arrow::struct_(schema->fields());
    std::shared_ptr<arrow::Array> struct_array = ArrowUtil::ArrayFromJSON(struct_type, json);

    // Convert StructArray to RecordBatch
    return *arrow::RecordBatch::FromStructArray(struct_array);
}

std::shared_ptr<arrow::Table> ArrowUtil::TableFromJSON(
    const std::shared_ptr<arrow::Schema>& schema,
    const std::vector<std::string>& json) {
    std::vector<std::shared_ptr<arrow::RecordBatch>> batches;
    for (const std::string& batch_json : json) {
        batches.push_back(ArrowUtil::RecordBatchFromJSON(schema, batch_json));
    }
    return *arrow::Table::FromRecordBatches(schema, std::move(batches));
}