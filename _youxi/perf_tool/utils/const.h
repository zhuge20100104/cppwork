#ifndef _FREDRIC_CONST_H_
#define _FREDRIC_CONST_H_

#include <string>

const int MIN_TIME_BOUND = 180000;
const int MAX_TIME_BOUND = -1;

const int MAX_BODY_LEN = 655360;
const std::string server_cfg_file_path = "../conf/server.conf";
const std::string master_cfg_file_path = "../conf/master.conf";
const std::string slave_cfg_file_path = "../conf/slave.conf";

const std::string cases_file_path = "../cases/single_test.json";

#endif