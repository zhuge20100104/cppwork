#include <boost/program_options.hpp>
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char* argv[]) {
	opt::options_description desc("All Options");
	
	int orange_var = 0;
	desc.add_options()
		("oranges,o", opt::value<int>(&orange_var)->required(),
		 	"oranges that you have")
		("name", opt::value<std::string>(), "Your name")
		("help", "produce help message")
		("apples,a", opt::value<int>()->default_value(10), 
		 "apples that you have");

	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);

	if(vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}
	
	// 读取配置文件中的配置信息
	try {
		opt::store(opt::parse_config_file<char>("apples_oranges.cfg", desc), vm);
	}catch(const opt::reading_file& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	try {
		// 填充值到vm中
		opt::notify(vm);
	}catch(const opt::required_option& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	if(vm.count("name")) {
		std::cout << "Hi, " << vm["name"].as<std::string>() << "!\n";
	}

	std::cout << "Fruits count: " <<
	       vm["apples"].as<int>() + vm["oranges"].as<int>()
	       << std::endl;
}

