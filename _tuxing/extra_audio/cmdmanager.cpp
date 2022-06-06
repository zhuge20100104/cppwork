#include "cmdmanager.h"

#include <iostream>


namespace opt = boost::program_options;

bool CmdManager::parse_command() {
	opt::options_description desc("抽取音频程序选项");
	desc.add_options()	
		("src", opt::value<std::string>()->required(), "源视频文件路径")
		("dst", opt::value<std::string>()->required(), "目标音频文件路径")
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
	std::string src_video = vm["src"].as<std::string>();
	std::string dst_audio = vm["dst"].as<std::string>();

	AUDIO_OP_ERRORS err = AUDIO_OP_ERRORS::NO_ERROR;
	audio_op.extract_audio(src_video, dst_audio, err);
	if(err != AUDIO_OP_ERRORS::NO_ERROR) {
		std::cerr << "抽取音频文件失败, Error: " << err << std::endl;
		return false;
	}

	return true;
}
