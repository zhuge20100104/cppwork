#ifndef _CMD_MANAGER_H_
#define _CMD_MANAGER_H_
#include "common_header.h"
#include "media_info.h"

#include <boost/program_options.hpp>

struct CmdManager {
	int argc_;
	char** argv_;
	
	CmdManager(int argc, char** argv): argc_(argc), argv_{argv} {}
	bool parse_command();
};

#endif
