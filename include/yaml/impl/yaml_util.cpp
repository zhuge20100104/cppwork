#include "yaml/yaml_util.h"

#include <iostream>

using yaml_op = YAML::EMITTER_MANIP;

std::string yaml_util::convert_map_objects_to_yaml(const objects_type& objs) {
    std::stringstream ss {};
    emitter_ emitt_{ss};
    emitt_ << yaml_op::BeginSeq;
    for(auto& object_map: objs) {
        emitt_ << yaml_op::BeginMap;
        for(auto object_field: object_map) {
            emitt_ << yaml_op::Key << object_field.first << yaml_op::Value << object_field.second;
        }
        emitt_ << yaml_op::EndMap;
    }
    emitt_ << yaml_op::EndSeq;
    return std::move(ss.str());
}

objects_type yaml_util::parse_objects_from_string(const std::string& objs_str) {
    auto nodes = YAML::Load(objs_str);
    objects_type res;
    for(auto&& node: nodes) {
        std::map<std::string, std::string> object = node.as<std::map<std::string, std::string>>();
        res.emplace_back(std::move(object));
    }
    return std::move(res);
}