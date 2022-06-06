#include "yaml/yaml_util.h"

#include <gtest/gtest.h>



GTEST_TEST(YamlUtilTests, ConvertMapObjectsToYaml) {
    objects_type cfgs = {
        {
        {"monitoring_category", "aso"}, 
        {"container_name", "ASO Keyword CPX"},
        {"container_id", "613eab5a375fa40534c32aa7-613eab4112acea05315b3b8e"}
        },
        {
        {"monitoring_category", "keyword"}, 
        {"container_name", "Product Keyword"},
        {"container_id", "613eab5a375fa40534c32aa7-613eabaf6e8609053a6276ea"}
        }};
    auto res = yaml_util::convert_map_objects_to_yaml(cfgs);
    ASSERT_TRUE(res.find("monitoring_category") != std::string::npos);
}


GTEST_TEST(YamlUtilTests, ParseObjectsFromString) {
    auto objs_str = R"(- container_id: 613eab5a375fa40534c32aa7-613eab4112acea05315b3b8e
  container_name: ASO Keyword CPX
  monitoring_category: aso
- container_id: 613eab5a375fa40534c32aa7-613eabaf6e8609053a6276ea
  container_name: Product Keyword
  monitoring_category: keyword)";

    auto res = yaml_util::parse_objects_from_string(objs_str);
    ASSERT_EQ(2, res.size());
}




