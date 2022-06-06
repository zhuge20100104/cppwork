#include <boost/program_options.hpp>

#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char* argv[]) {
    opt::options_description desc("All Options");
    desc.add_options()
        ("apples", opt::value<int>(), "how many apples do you have")
        ("oranges", opt::value<int>(), "how many oranges do you have")
        ("help", "produce help message");

    opt::variables_map vm;
    
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    opt::notify(vm);

    // 如果是带有help参数，那么直接打印描述信息
    if(vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if(!vm.count("apples") || !vm.count("oranges")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::cout << "Fruits count: " <<
        vm["apples"].as<int>() + vm["oranges"].as<int>()
        << std::endl;
}
