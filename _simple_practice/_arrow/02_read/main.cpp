#include <arrow/io/file.h>
#include <parquet/stream_reader.h>

#include <iostream>

struct Article {
    std::string name;
    float price;
    int quantity;
};

int main(int argc, char* argv[]) {
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, 
        arrow::io::ReadableFile::Open("test.parquet"));
    
    parquet::StreamReader is {parquet::ParquetFileReader::Open(infile)};

    Article arti;

    while(!is.eof()) {
        is >> arti.name >> arti.price >> arti.quantity >> parquet::EndRow;
        std::cout << arti.name << " " << arti.price << " " << arti.quantity << std::endl;
    }
}