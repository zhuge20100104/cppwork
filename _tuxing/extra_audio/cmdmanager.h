#ifndef _CMD_MANAGER_H_
#define _CMD_MANAGER_H_
#include "common_header.h"
#include "audio_op.h"

#include <boost/program_options.hpp>

struct CmdManager {
	int argc_;
	char** argv_;
	AudioOp audio_op {};
	CmdManager(int argc, char** argv): argc_(argc), argv_{argv} {}
	bool parse_command();
};

#endif
