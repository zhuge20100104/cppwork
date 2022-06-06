#include "f_copy.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

void TextFileCopy(const std::string& srcF, const std::string& dstF) {
    std::ifstream input{srcF};
    if (!input) {
        std::cout << "Source File not found" << std::endl;
        return;
    }

    std::filesystem::path destPath{dstF};
    if (std::filesystem::exists(destPath)) {
        std::cout << "File already exists, will override the exist file: "
                  << dstF << std::endl;
    }

    std::ofstream output{dstF};
    if (!output) {
        std::cout << "Could not open the dest file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        output << line << std::endl;
    }

    input.close();
    output.close();
}

void BinaryFileCopy(const std::string& srcF, const std::string& dstF) {
    std::ifstream input{srcF, std::ios::in | std::ios::binary};
    if (!input) {
        std::cout << "Could not open the source file" << std::endl;
        return;
    }

    if (std::filesystem::exists(dstF)) {
        std::cout << "File Already exists, will override the exists file: "
                  << dstF << std::endl;
    }

    std::ofstream output{dstF, std::ios::out | std::ios::binary};
    if (!output) {
        std::cout << "Could not open the destination file" << std::endl;
        return;
    }

    auto file_size = std::filesystem::file_size(srcF);
    const unsigned BufferSize = 512;
    char buffer[BufferSize]{};

    std::cout << "Copying: " << srcF;
    // 文件不到一个Buffer大
    if (file_size < BufferSize) {
        if (!input.read(buffer, file_size)) {
            throw std::runtime_error("Error occurred during read operation");
        }
        if (!output.write(buffer, file_size)) {
            throw std::runtime_error("Error occurred during write operation");
        }
    } else {
        // 大文件分为多个块来拷，并打印进度，进度乘10，是为了不让结果看起来都是0，一直不打印
        auto chunks = file_size / BufferSize;
        // 这里用int是因为 剩余大小小于 512，用int就可以了，不需要 std::size_t
        int remaining = file_size % BufferSize;
        int progress{}, oldProgress{};
        for (int i = 0; i < chunks; ++i) {
            if (!input.read(buffer, BufferSize)) {
                throw std::runtime_error(
                    "Error occurred during read operation");
            }

            if (!output.write(buffer, BufferSize)) {
                throw std::runtime_error(
                    "Error occurred during write operation");
            }

            // 先转浮点避免全零，再转整型便于比较
            // 类型转换建议使用 static_cast，不要直接强转
            // 因为static_cast会做类型检查
            progress = static_cast<int>((10 * static_cast<float>(i) / chunks));
            if (progress != oldProgress) {
                std::cout << '.';
            }
            oldProgress = progress;
        }

        // 下一次的读取将会小于 BufferSize
        // 但是buffer 里面可能还有上次读取的残存数据，
        // 所以需要使用memset清空
        // 比较底层的C操作，但是没办法，因为读写二进制必须按char* [byte]处理
        memset(buffer, '\0', BufferSize);

        if (remaining > 0) {
            if (!input.read(buffer, remaining)) {
                throw std::runtime_error(
                    "Error occurred during read operation");
            }
            if (!output.write(buffer, remaining)) {
                throw std::runtime_error(
                    "Error occurred during write operation");
            }
            std::cout << '.';
        }

        std::cout << "Done! " << std::endl;

        input.close();
        output.close();
    }
}