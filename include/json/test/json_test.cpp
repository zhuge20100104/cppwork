#include "json/json.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

using json = nlohmann::json;


int main(int argc, char **argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


GTEST_TEST(JsonTests, FirstJson) {
    auto old_value_str = R"({"default": ["gp/20600000009072/JelCBr0rDjDEGOqYb4m2Z7OSVBxS5KyqO94eW5TGnQtHc9k08uaMZVTz6s_rKha31eE=w720-h310", "gp/20600000009072/Iomoub5EHkAk1_bKqIyjkFbKQ4vw-zFfTqfUMG_da-4-hV_tXwvuiFQUQWIeol_fRSo=w720-h310", "gp/20600000009072/Jx0nPnGaGNRXCHlmGv13gDsIzhLykgkza5y2SUNruZoiwcik5lQ-gj99vdHZA0Zlbtrz=w720-h310", "gp/20600000009072/YBTVMqZcl-t16dnH7_DxHsMm7WU2v2HdZRX3Q3UnYHXo8HUfQSuN2Ahn_M4KQunbeigu=w720-h310", "gp/20600000009072/o4enSNrWkR4F6wILxPk6-6XkNyea4j9tcn8gLPphbBvhpp4_HBU9NNuQnhzreYH5uSN0=w720-h310"]})";

    auto old_value = json::parse(old_value_str);
    auto old_list = old_value["default"];

    std::cout << old_list << std::endl;
    ASSERT_EQ("gp/20600000009072/JelCBr0rDjDEGOqYb4m2Z7OSVBxS5KyqO94eW5TGnQtHc9k08uaMZVTz6s_rKha31eE=w720-h310", old_list[0]);
    ASSERT_EQ("gp/20600000009072/Iomoub5EHkAk1_bKqIyjkFbKQ4vw-zFfTqfUMG_da-4-hV_tXwvuiFQUQWIeol_fRSo=w720-h310", old_list[1]);
    ASSERT_EQ("gp/20600000009072/Jx0nPnGaGNRXCHlmGv13gDsIzhLykgkza5y2SUNruZoiwcik5lQ-gj99vdHZA0Zlbtrz=w720-h310", old_list[2]);
    ASSERT_EQ("gp/20600000009072/YBTVMqZcl-t16dnH7_DxHsMm7WU2v2HdZRX3Q3UnYHXo8HUfQSuN2Ahn_M4KQunbeigu=w720-h310", old_list[3]);
    ASSERT_EQ("gp/20600000009072/o4enSNrWkR4F6wILxPk6-6XkNyea4j9tcn8gLPphbBvhpp4_HBU9NNuQnhzreYH5uSN0=w720-h310", old_list[4]);

    ASSERT_EQ(5, old_list.size());
}

GTEST_TEST(JsonTests, CompareTest) {
    auto js_str = R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}])";

    auto js = json::parse(js_str);
    std::sort(js.begin(), js.end());
    auto js1 = json::parse(js_str);

    // Order are not equal for js and js1
    ASSERT_TRUE(js!=js1);
}


GTEST_TEST(JsonTests, SortTest) {
    

    auto js_str = R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}, {"name": "WangWu", "age": 28}])";

    auto js = json::parse(js_str);
    std::sort(js.begin(), js.end());
    auto expect_str = R"([{"age":18,"name":"Zhangsan"},{"age":20,"name":"Lisi"},{"age":28,"name":"WangWu"}])";
    ASSERT_EQ(expect_str, js.dump());

    auto js_age_eq_str = R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 20}, {"name": "WangWu", "age": 20}])";
    auto js_age_eq = json::parse(js_age_eq_str);
    std::sort(js_age_eq.begin(), js_age_eq.end());
    auto expect_age_eq_str = R"([{"age":20,"name":"Lisi"},{"age":20,"name":"WangWu"},{"age":20,"name":"Zhangsan"}])";
    
    LOG(INFO) << js_age_eq.dump() << "\n";

    ASSERT_EQ(expect_age_eq_str, js_age_eq.dump());
}