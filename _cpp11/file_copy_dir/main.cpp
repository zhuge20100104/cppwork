#include "f_copy.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::filesystem::path cur_path = std::filesystem::current_path();
    std::filesystem::path srcDir {cur_path};
    std::filesystem::path dstDir {cur_path.parent_path()};
    srcDir /= "CMakeFiles";
    dstDir /= "target_cmake";
    
    CopyDir(srcDir, dstDir);
}