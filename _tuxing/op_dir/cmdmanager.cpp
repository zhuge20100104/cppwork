#include "cmdmanager.h"

#include <iostream>


namespace opt = boost::program_options;

bool CmdManager::parse_command() {
	opt::options_description desc("目录列表程序选项");
	desc.add_options()	
		("op", opt::value<std::string>()->required(), "文件操作选项, list, move, delete")
		("src", opt::value<std::string>()->required(), "源文件目录")
		("dst", opt::value<std::string>(), "目标文件目录")
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
	std::string op = vm["op"].as<std::string>();
	FILE_OP_ERRORS err = FILE_OP_ERRORS::NO_ERROR;
	std::string src_dir = vm["src"].as<std::string>();
	if(op == "list") {
		audio_op.list_dir(src_dir, err);
	}else if(op == "move") {
		std::string dst_dir = vm["dst"].as<std::string>();
		audio_op.move_dir(src_dir, dst_dir, err);
	}else if(op == "delete") {
		audio_op.delete_dir(src_dir, err);
	}else {
		std::cerr << "不支持的操作选项" << std::endl;
	}
	// 说明有出错
	if(err != FILE_OP_ERRORS::NO_ERROR) {
		std::cerr << op << "失败" 
			<< "Error: " << err
			<< std::endl;
	}
	return true;
}
