#ifndef _FREDRIC_YAML_UTIL_H_
#define _FREDRIC_YAML_UTIL_H_
#include <yaml-cpp/yaml.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>

using emitter_ = YAML::Emitter;
using parser_ = YAML::Parser;
using objects_type = std::vector<std::map<std::string, std::string>>;

struct yaml_util {
    static std::string convert_map_objects_to_yaml(const objects_type& objs);
    static objects_type parse_objects_from_string(const std::string& objs_str);
};
#endif