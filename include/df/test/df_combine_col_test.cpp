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

static double my_max_3(double const& d1, double const& d2, double const& d3) {
    return std::max<double>({d1, d2, d3});
}

static double my_max_4(double const& d1, double const& d2, double const& d3, double const& d4) {
    return std::max<double>({d1, d2, d3, d4});
}

GTEST_TEST(DFCombineColTests, CombineThreeCol) {
    // 三列合并取最大值
    LOG(INFO) << "\nTesting combine() three cols ...\n";

    std::vector<unsigned long> idx1 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx2 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx3 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx4 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<double> d1 {
        1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 300, 13, 14, 15, 16, 17, 18, 19, 20, 200
    };
    std::vector<double> d2 {
        1, 2, 1000, 4, 5, 6, 7, 8, 9, 10, 11, 3000, 13, 14, 15, 16, 17, 18, 19, 20, 2000
    };
    std::vector<double> d3 {
        1, 2, 5000, 4, 5, 6, 7, 8, 9, 10, 11, 7000, 13, 14, 15, 16, 17, 18, 19, 20, 8000 
    };
    std::vector<double> d4 {
        1, 2, 10000, 4, 5, 6, 7, 8, 9, 10, 11, 20000, 13, 14, 15, 16, 17, 18, 19, 20, 30000
    };

    CLDataFrame df1, df2, df3, df4;

    df1.load_data(
        std::move(idx1),
        std::make_pair("d1_col", d1)
    );

    df2.load_data(
        std::move(idx2),
        std::make_pair("d1_col", d2)
    );

    df3.load_data(
        std::move(idx3),
        std::make_pair("d1_col", d3)
    );

    df4.load_data(
        std::move(idx4),
        std::make_pair("d1_col", d4)
    );

    df1.load_column("d2_col", std::move(df1.combine<double>("d1_col", df2, df3, my_max_3)));

    df1.write<std::ostream, double>(std::cout);

    std::vector<double> result {1,2,5000,4,5,6,7,8,9,10,11,7000,13,14,15,16,17,18,19,20,8000};
    ASSERT_EQ(result, df1.get_column<double>("d2_col"));
}

GTEST_TEST(DFCombineColTests, CombineFourCol) {
    // 4列合并取最大值
    LOG(INFO) << "\nTesting combine() four cols ...\n";

    std::vector<unsigned long> idx1 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx2 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx3 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<unsigned long> idx4 {
        123450, 123451, 123452, 123453, 123454, 123455, 123456,
        123457, 123458, 123459, 123460, 123461, 123462, 123466,
        123467, 123468, 123469, 123470, 123471, 123472, 123473
    };

    std::vector<double> d1 {
        1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 300, 13, 14, 15, 16, 17, 18, 19, 20, 200
    };
    std::vector<double> d2 {
        1, 2, 1000, 4, 5, 6, 7, 8, 9, 10, 11, 3000, 13, 14, 15, 16, 17, 18, 19, 20, 2000
    };
    std::vector<double> d3 {
        1, 2, 5000, 4, 5, 6, 7, 8, 9, 10, 11, 7000, 13, 14, 15, 16, 17, 18, 19, 20, 8000 
    };
    std::vector<double> d4 {
        1, 2, 10000, 4, 5, 6, 7, 8, 9, 10, 11, 20000, 13, 14, 15, 16, 17, 18, 19, 20, 30000
    };

    CLDataFrame df1, df2, df3, df4;

    df1.load_data(
        std::move(idx1),
        std::make_pair("d1_col", d1)
    );

    df2.load_data(
        std::move(idx2),
        std::make_pair("d1_col", d2)
    );

    df3.load_data(
        std::move(idx3),
        std::make_pair("d1_col", d3)
    );

    df4.load_data(
        std::move(idx4),
        std::make_pair("d1_col", d4)
    );

    df1.load_column("d2_col", std::move(df1.combine<double>("d1_col", df2, df3, df4, my_max_4)));

    df1.write<std::ostream, double>(std::cout);

    std::vector<double> result {1, 2, 10000, 4, 5, 6, 7, 8, 9, 10, 11, 20000, 13, 14, 15, 16, 17, 18, 19, 20, 30000};
    ASSERT_EQ(result, df1.get_column<double>("d2_col"));
}
