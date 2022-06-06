#ifndef _FREDRIC_ARR__H_
#define _FREDRIC_ARR__H_

#define ARROW_COMPUTE

#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/compute/exec/exec_plan.h>
#include <arrow/csv/api.h>
#include <arrow/dataset/api.h>
#include <arrow/filesystem/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/json/api.h>
#include <arrow/pretty_print.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <arrow/testing/gtest_util.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "arrow/pretty_print.h"
#include "arrow/util/async_generator.h"
#include "arrow/util/logging.h"
#include "arrow/util/thread_pool.h"
#include "arrow/util/vector.h"

template <typename T>
using numbuildT = arrow::NumericBuilder<T>;

using boolbuild = arrow::BooleanBuilder;

struct BatchesWithSchema {
    std::vector<arrow::compute::ExecBatch> batches;
    std::shared_ptr<arrow::Schema> schema;
};

struct ArrowUtil {
    static arrow::Status read_csv(char const* file_name,
                                  std::shared_ptr<arrow::Table>& tb);
    static arrow::Status read_ipc(char const* file_name,
                                  std::shared_ptr<arrow::Table>& tb);
    static arrow::Status read_parquet(char const* file_name,
                                      std::shared_ptr<arrow::Table>& tb);
    static arrow::Status read_json(char const* file_name,
                                   std::shared_ptr<arrow::Table>& tb);
    static arrow::Status write_ipc(arrow::Table const& tb,
                                   char const* file_name);
    static arrow::Status write_parquet(arrow::Table const& tb,
                                       char const* file_name);

    static std::shared_ptr<arrow::Table> TableFromJSON(
        const std::shared_ptr<arrow::Schema>& schema,
        const std::vector<std::string>& json);

    static std::shared_ptr<arrow::RecordBatch> RecordBatchFromJSON(
        const std::shared_ptr<arrow::Schema>& schema, std::string const& json);

    static std::shared_ptr<arrow::Array> ArrayFromJSON(
        const std::shared_ptr<arrow::DataType>& type, std::string const& json);

    static void SleepFor(double seconds) {
        std::this_thread::sleep_for(
            std::chrono::nanoseconds(static_cast<int64_t>(seconds * 1e9)));
    }
    
    static arrow::Result<arrow::util::optional<std::string>> PrintArrayDiff(
        const arrow::ChunkedArray& expected, const arrow::ChunkedArray& actual) {
        if (actual.Equals(expected)) {
            return arrow::util::nullopt;
        }

        std::stringstream ss;
        if (expected.length() != actual.length()) {
            ss << "Expected length " << expected.length()
               << " but was actually " << actual.length();
            return ss.str();
        }

        arrow::PrettyPrintOptions options(/*indent=*/2);
        options.window = 50;
        RETURN_NOT_OK(arrow::internal::ApplyBinaryChunked(
            actual, expected,
            [&](const arrow::Array& left_piece, const arrow::Array& right_piece,
                int64_t position) {
                std::stringstream diff;
                if (!left_piece.Equals(right_piece,
                                       arrow::EqualOptions().diff_sink(&diff))) {
                    ss << "Unequal at absolute position " << position << "\n"
                       << diff.str();
                    ss << "Expected:\n";
                    ARROW_EXPECT_OK(arrow::PrettyPrint(right_piece, options, &ss));
                    ss << "\nActual:\n";
                    ARROW_EXPECT_OK(arrow::PrettyPrint(left_piece, options, &ss));
                }
                return arrow::Status::OK();
            }));
        return ss.str();
    }

    static void AssertChunkedEqual(const arrow::ChunkedArray& expected,
                                   const arrow::ChunkedArray& actual) {
        ASSERT_EQ(expected.num_chunks(), actual.num_chunks())
            << "# chunks unequal";
        if (!actual.Equals(expected)) {
            std::stringstream diff;
            for (int i = 0; i < actual.num_chunks(); ++i) {
                auto c1 = actual.chunk(i);
                auto c2 = expected.chunk(i);
                diff << "# chunk " << i << std::endl;
                ARROW_IGNORE_EXPR(
                    c1->Equals(c2, arrow::EqualOptions().diff_sink(&diff)));
            }
            FAIL() << diff.str();
        }
    }
    static void AssertTablesEqual(const arrow::Table& expected,
                                  const arrow::Table& actual,
                                  bool same_chunk_layout, bool combine_chunks) {
        ASSERT_EQ(expected.num_columns(), actual.num_columns());

        if (combine_chunks) {
            auto pool = arrow::default_memory_pool();
            ASSERT_OK_AND_ASSIGN(auto new_expected,
                                 expected.CombineChunks(pool));
            ASSERT_OK_AND_ASSIGN(auto new_actual, actual.CombineChunks(pool));

            AssertTablesEqual(*new_expected, *new_actual, false, false);
            return;
        }

        if (same_chunk_layout) {
            for (int i = 0; i < actual.num_columns(); ++i) {
                AssertChunkedEqual(*expected.column(i), *actual.column(i));
            }
        } else {
            std::stringstream ss;
            for (int i = 0; i < actual.num_columns(); ++i) {
                auto actual_col = actual.column(i);
                auto expected_col = expected.column(i);

                ASSERT_OK_AND_ASSIGN(
                    auto diff, PrintArrayDiff(*expected_col, *actual_col));
                if (diff.has_value()) {
                    FAIL() << *diff;
                }
            }
        }
    }

    template <typename T, typename buildT, typename arrayT>
    inline static std::shared_ptr<arrow::Array> chunked_array_to_array(
        std::shared_ptr<arrow::ChunkedArray> const& array_a) {
        buildT int64_builder;
        int64_builder.Resize(array_a->length());
        std::vector<T> int64_values;
        int64_values.reserve(array_a->length());
        for (int i = 0; i < array_a->num_chunks(); ++i) {
            auto inner_arr = array_a->chunk(i);
            auto int_a = std::static_pointer_cast<arrayT>(inner_arr);
            for (int j = 0; j < int_a->length(); ++j) {
                int64_values.push_back(int_a->Value(j));
            }
        }

        int64_builder.AppendValues(int64_values);
        std::shared_ptr<arrow::Array> array_a_res;
        int64_builder.Finish(&array_a_res);
        return array_a_res;
    }

    template <typename T, typename arrayT>
    inline static std::vector<T> chunked_array_to_vector(
        std::shared_ptr<arrow::ChunkedArray> const& array_a) {
        std::vector<T> int64_values;
        int64_values.reserve(array_a->length());
        for (int i = 0; i < array_a->num_chunks(); ++i) {
            auto inner_arr = array_a->chunk(i);
            auto int_a = std::static_pointer_cast<arrayT>(inner_arr);
            for (int j = 0; j < int_a->length(); ++j) {
                int64_values.push_back(int_a->Value(j));
            }
        }
        return int64_values;
    }

    inline static std::vector<std::string> chunked_array_to_str_vector(
        std::shared_ptr<arrow::ChunkedArray> const& array_a) {
        std::vector<std::string> int64_values;
        int64_values.reserve(array_a->length());
        for (int i = 0; i < array_a->num_chunks(); ++i) {
            auto inner_arr = array_a->chunk(i);
            auto int_a =
                std::static_pointer_cast<arrow::StringArray>(inner_arr);
            for (int j = 0; j < int_a->length(); ++j) {
                int64_values.push_back(int_a->Value(j).to_string());
            }
        }
        return int64_values;
    }

    inline static std::shared_ptr<arrow::Array> chunked_array_to_str_array(
        std::shared_ptr<arrow::ChunkedArray> const& array_a) {
        arrow::StringBuilder int64_builder;
        int64_builder.Resize(array_a->length());
        std::vector<std::string> int64_values;
        int64_values.reserve(array_a->length());
        for (int i = 0; i < array_a->num_chunks(); ++i) {
            auto inner_arr = array_a->chunk(i);
            auto int_a =
                std::static_pointer_cast<arrow::StringArray>(inner_arr);
            for (int j = 0; j < int_a->length(); ++j) {
                int64_values.push_back(int_a->Value(j).to_string());
            }
        }
        int64_builder.AppendValues(int64_values);
        std::shared_ptr<arrow::Array> array_a_res;
        int64_builder.Finish(&array_a_res);
        return array_a_res;
    }

    static arrow::Result<arrow::compute::ExecNode*> MakeTestSourceNode(
        arrow::compute::ExecPlan* plan, std::string label,
        BatchesWithSchema batches_with_schema, bool parallel, bool slow);

    static arrow::Future<std::vector<arrow::compute::ExecBatch>>
    StartAndCollect(
        arrow::compute::ExecPlan* plan,
        arrow::AsyncGenerator<arrow::util::optional<arrow::compute::ExecBatch>>
            gen);

    static BatchesWithSchema MakeBatchAndSchema(
        std::shared_ptr<arrow::Table> const& tb);
    static arrow::Status ConvertExecBatchToRecBatch(
        std::shared_ptr<arrow::Schema> const& schema,
        std::vector<arrow::compute::ExecBatch> const& exec_batches,
        arrow::RecordBatchVector& out_rec_batches);
};

#endif