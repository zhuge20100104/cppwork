#include "cmdmanager.h"

#include <iostream>


namespace opt = boost::program_options;

bool CmdManager::parse_command() {
	opt::options_description desc("打印媒体信息");
	desc.add_options()	
		("src", opt::value<std::string>()->required(), "音频文件位置")
		("help", "print this help command");

	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc_, argv_, desc), vm);
	
	if(vm.count("help")) {
		std::cout << desc << std::endl;
		return true;
	}
	try {
		opt::notify(vm);
	}catch(const opt::required_option& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return false;
	}
	std::string filename = vm["src"].as<std::string>();

	MediaInfo media_info { filename };
	// 打印媒体文件信息
	media_info.printInfo();
	return true;
}
