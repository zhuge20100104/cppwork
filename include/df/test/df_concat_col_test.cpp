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

GTEST_TEST(DFConcatColTests, SelfConcatCol) {
    // 改变self
    LOG(INFO) << "\nTesting self_concat( ) ...\n";
    CLDataFrame df1;
    std::vector<unsigned long> idxvec {1UL, 2UL, 3UL, 10UL, 5UL, 7UL, 8UL, 12UL, 9UL, 12UL, 10UL, 13UL, 10UL, 15UL, 14UL};

    std::vector<double> dblvec {0.0, 15.0, 14.0, 2.0, 1.0, 12.0, 11.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 9.0, 10.0};

    std::vector<double> dblvec2 {100.0, 101.0, 102.0, 103.0, 104.0, 105.0, 106.55, 107.34, 1.8, 111.0, 112.0, 113.0, 114.0, 115.0, 116.0};

    std::vector<int> intvec {1, 2, 3, 4, 5, 8, 6, 7, 11, 14, 9, 10, 15, 12, 13};

    std::vector<std::string> strvec {"zz", "bb", "cc", "ww", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo"};

    df1.load_data(std::move(idxvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("int_col", intvec),
        std::make_pair("str_col", strvec));
    
    // 深拷贝df1到df2
    CLDataFrame df2 = df1;

    df2.load_column("dbl_col_2", std::move(dblvec2));
    df1.self_concat<decltype(df2), double, int, std::string>(df2, true);
    df1.write<std::ostream, double, int, std::string>(std::cout);

    ASSERT_EQ(30, df1.get_index().size());
    ASSERT_EQ(30, df1.get_column<double>("dbl_col").size());
    ASSERT_EQ(30, df1.get_column<double>("dbl_col_2").size());
    ASSERT_EQ(30, df1.get_column<int>("int_col").size());
    ASSERT_EQ(30, df1.get_column<std::string>("str_col").size());

    ASSERT_EQ(0.0, df1.get_column<double>("dbl_col")[0]);
    ASSERT_EQ(0.0, df1.get_column<double>("dbl_col")[15]);
    ASSERT_TRUE(std::isnan(df1.get_column<double>("dbl_col_2")[0]));
    ASSERT_TRUE(std::isnan(df1.get_column<double>("dbl_col_2")[14]));
}

GTEST_TEST(DFConcatColTests, ConcatCol) {
    // 不改变self
    LOG(INFO) << "\nTesting concat( ) ...\n";

    CLDataFrame df1;
    std::vector<unsigned long> idxvec {1UL, 2UL, 3UL, 10UL, 5UL, 7UL, 8UL, 12UL, 9UL, 12UL, 10UL, 13UL, 10UL, 15UL, 14UL};

    std::vector<double> dblvec {0.0, 15.0, 14.0, 2.0, 1.0, 12.0, 11.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 9.0, 10.0};

    std::vector<double> dblvec2 {100.0, 101.0, 102.0, 103.0, 104.0, 105.0, 106.55, 107.34, 1.8, 111.0, 112.0, 113.0, 114.0, 115.0, 116.0};

    std::vector<int> intvec {1, 2, 3, 4, 5, 8, 6, 7, 11, 14, 9, 10, 15, 12, 13};

    std::vector<std::string> strvec {"zz", "bb", "cc", "ww", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo"};

    df1.load_data(std::move(idxvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("int_col", intvec),
        std::make_pair("str_col", strvec));
    
    // 深拷贝df1到df2
    CLDataFrame df2 = df1;
    df2.load_column("dbl_col_2", std::move(dblvec2));

    // 连接选项 concat_policy::all_columns
    auto result = df1.concat<decltype(df2), double, int, std::string>(df2); 
    result.write<std::ostream, double, int, std::string>(std::cout);

    ASSERT_EQ(30, result.get_index().size());
    ASSERT_EQ(30, result.get_column<double>("dbl_col").size());
    ASSERT_EQ(30, result.get_column<double>("dbl_col_2").size());
    ASSERT_EQ(30, result.get_column<int>("int_col").size());
    ASSERT_EQ(30, result.get_column<std::string>("str_col").size());

    ASSERT_EQ(0.0, result.get_column<double>("dbl_col")[0]);
    ASSERT_EQ(0.0, result.get_column<double>("dbl_col")[15]);
    ASSERT_TRUE(std::isnan(result.get_column<double>("dbl_col_2")[0]));
    ASSERT_TRUE(std::isnan(result.get_column<double>("dbl_col_2")[14]));

    // 连接选项 concat_policy::common_columns
    auto result2 = df1.concat<decltype(df2), double, int, std::string>(df2, concat_policy::common_columns);

    result2.write<std::ostream, double, int, std::string>(std::cout);
    ASSERT_TRUE(!result2.has_column("dbl_col_2"));
}