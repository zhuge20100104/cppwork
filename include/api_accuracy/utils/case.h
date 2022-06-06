#ifndef _FREDRIC_CASE_H_
#define _FREDRIC_CASE_H_
#include <string>

struct Case {
    std::string name;
    std::string url;
    int expect_code;
};

struct AsyncCase {
    std::string name; 
    std::string sync_url;
    int sync_code; 
    std::string async_url;
    int async_code;
};
#endif