#include <arrow/io/hdfs.h>

#include <parquet/stream_reader.h>

#include <iostream>

struct Article {
    std::string name;
    float price;
    int quantity;
};

int main(int argc, char* argv[]) {

    std::shared_ptr<arrow::io::HadoopFileSystem> fs;
    std::unordered_map<std::string, std::string> extraConf;
    arrow::io::HdfsConnectionConfig connectCfg {"172.18.0.2", 0, "root", "", extraConf};

    auto connectRes = arrow::io::HadoopFileSystem::Connect(&connectCfg , &fs);

    if(!connectRes.ok()) {
        std::cerr << "连接到HDFS失败, Error: " << connectRes.message() << std::endl;
        return -1;
    }

    
    std::shared_ptr<arrow::io::HdfsReadableFile> infile;
    auto streamRes = fs->OpenReadable("/test.parquet", false, &infile);

    if(!streamRes.ok()) {
        std::cerr << "连接到HDFS失败, Error: " << streamRes.message() << std::endl;
        return -2;
    }
    
    
    parquet::StreamReader is {parquet::ParquetFileReader::Open(infile)};

    Article arti;

    while(!is.eof()) {
        is >> arti.name >> arti.price >> arti.quantity >> parquet::EndRow;
        std::cout << arti.name << " " << arti.price << " " << arti.quantity << std::endl;
    }
    
    return 0;
}