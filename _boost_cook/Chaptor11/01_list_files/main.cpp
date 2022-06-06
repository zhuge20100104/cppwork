#include <boost/filesystem/operations.hpp>
#include <boost/version.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;

    boost::filesystem::directory_iterator begin("./");
    boost::filesystem::directory_iterator end;

    for(; begin!=end; ++begin) {
        boost::filesystem::file_status f = begin->status();

        switch(f.type()) {
            case boost::filesystem::regular_file:
                std::cout << "FILE  ";
                break;
            case boost::filesystem::symlink_file:
                std::cout << "SYMLINK   ";
                break;
            case boost::filesystem::directory_file:
                std::cout << "DIRECTORY ";
                break;
            default:
                std::cout << "OTHER ";
                break;
        }

        if(f.permissions() & boost::filesystem::owner_write) {
            std::cout << "W ";
        } else {
            std::cout << "  ";
        }

        std::cout << begin->path() << "\n";
    }
}