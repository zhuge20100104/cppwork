#include "gzip/gzip_reader.h"
#include "gzip/decompress.hpp"

#include <iostream>
#include <fstream>

std::string gzip_reader::read_file(const std::string& file_name) {
    std::string filename(file_name);
    std::ifstream stream(filename, std::ios_base::in | std::ios_base::binary);
    if (!stream.is_open())
    {
        throw std::runtime_error("could not open: '" + filename + "'");
    }
    std::string str_compressed((std::istreambuf_iterator<char>(stream.rdbuf())),
                               std::istreambuf_iterator<char>());
    stream.close();

    gzip::Decompressor decomp;
    std::string output;
    decomp.decompress(output, str_compressed.data(), str_compressed.size());
    return std::move(output);
}