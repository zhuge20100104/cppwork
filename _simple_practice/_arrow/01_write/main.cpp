#include <arrow/io/file.h>
#include <arrow/io/hdfs.h>

#include <parquet/stream_writer.h>

#include <iostream>
#include <string>
#include <vector>

struct Article {
    std::string name;
    float price;
    int quantity;
};

std::vector<Article> get_articles() {
    std::vector<Article> articles {
        Article {"南昌好景色", 35.0f, 20},
        Article {"武汉好风景", 24.0f, 30},
        Article {"北京王府井", 50.0f, 10}
    };
    return std::move(articles);
}

int main(int argc, char* argv[]) {
    std::shared_ptr<arrow::io::FileOutputStream> out_file;
    PARQUET_ASSIGN_OR_THROW(out_file, arrow::io::FileOutputStream::Open("test.parquet"));
    
    parquet::WriterProperties::Builder builder;
    
    // std::shared_ptr<arrow::io::HadoopFileSystem> fs;
    // arrow::io::HadoopFileSystem::Connect( ,fs);

    parquet::schema::NodeVector fields;

    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "name", parquet::Repetition::OPTIONAL, parquet::Type::BYTE_ARRAY,
        parquet::ConvertedType::UTF8));

    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "price", parquet::Repetition::REQUIRED, parquet::Type::FLOAT,
        parquet::ConvertedType::NONE, -1));

    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "quantity", parquet::Repetition::REQUIRED, parquet::Type::INT32,
        parquet::ConvertedType::INT_32, -1));
    
    std::shared_ptr<parquet::schema::GroupNode> schema = std::static_pointer_cast<parquet::schema::GroupNode>(
      parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));

    parquet::StreamWriter os {parquet::ParquetFileWriter::Open(out_file, schema, builder.build())};

    for(const auto& a: get_articles()) {
        os << a.name << a.price << a.quantity << parquet::EndRow;
    }
}