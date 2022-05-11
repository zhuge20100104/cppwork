#include "f_copy.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::filesystem::path cur_path = std::filesystem::current_path().parent_path();
    std::filesystem::path textSrcF {cur_path};
    std::filesystem::path textDstF {cur_path};
    textSrcF /= "main.cpp";
    textDstF /= "dst.cpp";
    TextFileCopy(textSrcF, textDstF);

    std::filesystem::path binSrcF {R"(/Users/aabjfzhu/spark-snowflake_2.11-2.8.5-spark_2.4.jar)"};
    std::filesystem::path binDstF {cur_path};
    binDstF /= "spark-snowflake.jar";
    BinaryFileCopy(binSrcF, binDstF);
    return 0;
}