#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

using ptree = boost::property_tree::ptree;

// 将boost::property_tree::ptree 对象转换成json字符串的函数
inline std::string ptreeToJsonString(const ptree& tree) {
    std::stringstream ss;
    boost::property_tree::write_json(ss, tree, false);
    return ss.str();
}



#endif
