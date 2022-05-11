#include "df/df.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "json/json.hpp"

#include <fstream>
#include <sstream>

using json = nlohmann::json;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

GTEST_TEST(DFTests, ConcatTest) {

    auto js_str =
        R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}, {"name": "WangWu", "age": 28}])";
    
    auto js_str1 =
        R"([{"name": "WangWu", "age": 28}, {"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}])";

    auto js = json::parse(js_str);
    auto js1 = json::parse(js_str1);

    std::vector<std::string> pri_keys{};
    auto df = df_op::convert_json_to_df(js, pri_keys);
    auto df1 = df_op::convert_json_to_df(js1, pri_keys);
    
    auto df3 = df.concat<decltype(df1), json>(df1, concat_policy::all_columns);

    df3.write<std::ostream, json>(LOG(INFO));

    std::vector<std::string> keys_{Keys};
    auto df4 = df_op::remove_duplicate(df3, keys_);

    df4.write<std::ostream, json>(LOG(INFO));

    LOG(INFO) << df4.shape().first<< " " << df4.shape().second << "\n";
    auto df_rows = df4.shape().first;
    ASSERT_EQ(0, df_rows);
}

GTEST_TEST(DFTests, JoinByAllTest) {

    auto js_str =
        R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}, {"name": "WangWu", "age": 28}])";
    
    auto js_str1 =
        R"([{"name": "WangWu", "age": 38}, {"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}])";

    auto js = json::parse(js_str);
    auto js1 = json::parse(js_str1);
   
    std::vector<std::string> pri_keys{};
    auto df = df_op::convert_json_to_df(js, pri_keys);
    auto df1 = df_op::convert_json_to_df(js1, pri_keys);

    auto df3 = df.join_by_column<decltype(df1), json, json, json>(df1, Keys.c_str(), join_policy::inner_join); 

    df3.write<std::ostream, json>(LOG(INFO));
    
    df_op::write_to_csv(df3, "./2.csv");
    ASSERT_EQ(2, df3.shape().first);
}

GTEST_TEST(DFTests, JoinByNameTest) {
    auto js_str =
        R"([{"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}, {"name": "WangWu", "age": 28}])";
    
    auto js_str1 =
        R"([{"name": "WangWu", "age": 38}, {"name": "Lisi", "age": 20}, {"name": "Zhangsan", "age": 18}])";

    auto js = json::parse(js_str);
    auto js1 = json::parse(js_str1);
   
    std::vector<std::string> pri_keys{"name"};
    auto df = df_op::convert_json_to_df(js, pri_keys);
    auto df1 = df_op::convert_json_to_df(js1, pri_keys);

    auto df3 = df.join_by_column<decltype(df1), json, json, json>(df1, Keys.c_str(), join_policy::inner_join); 

    df3.write<std::ostream, json>(LOG(INFO));
    
    df_op::write_to_csv(df3, "./3.csv");
    ASSERT_EQ(3, df3.shape().first);
} 