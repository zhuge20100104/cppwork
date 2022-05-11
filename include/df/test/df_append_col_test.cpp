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

GTEST_TEST(DFAppendColTests, AppendCol) {
    CLDataFrame df;
    std::vector<int> intvec {1, 2, 3, 4, 5};
    std::vector<double> dblvec {1.2345, 2.2345, 3.2345, 4.2345, 5.2345};
    std::vector<double> dblvec2 {0.998, 0.3456, 0.056, 0.15678, 0.00345, 0.923, 0.06743, 0.1 };
    std::vector<std::string> strvec {"Col_name", "Col_name", "Col_name", "Col_name", "Col_name"};

    std::vector<unsigned long> ulgvec {1UL, 2UL, 3UL, 4UL, 5UL, 8UL, 7UL, 6UL};
    auto xulgvec {ulgvec};

    auto rc = df.load_data(
        std::move(ulgvec),
        std::make_pair("int_col", intvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("dbl_col2", dblvec2),
        std::make_pair("str_col", strvec),
        std::make_pair("ul_col", xulgvec)
    );


    df.append_column<std::string>("str_col", "Additional column");
    df.append_column<double>("dbl_col", 10.56);
    df.write<std::ostream, int, double, std::string, unsigned long>(std::cout);
    ASSERT_EQ(10.56, df.get_column<double>("dbl_col")[8]);
    ASSERT_EQ("Additional column", df.get_column<std::string>("str_col")[8]);
}

GTEST_TEST(DFAppendColTests, AppendIdxes) {
    CLDataFrame df;
    std::vector<int> intvec {1, 2, 3, 4, 5};
    std::vector<double> dblvec {1.2345, 2.2345, 3.2345, 4.2345, 5.2345};
    std::vector<double> dblvec2 {0.998, 0.3456, 0.056, 0.15678, 0.00345, 0.923, 0.06743, 0.1 };
    std::vector<std::string> strvec {"Col_name", "Col_name", "Col_name", "Col_name", "Col_name"};

    std::vector<unsigned long> ulgvec {1UL, 2UL, 3UL, 4UL, 5UL, 8UL, 7UL, 6UL};
    auto xulgvec {ulgvec};

    auto rc = df.load_data(
        std::move(ulgvec),
        std::make_pair("int_col", intvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("dbl_col2", dblvec2),
        std::make_pair("str_col", strvec),
        std::make_pair("ul_col", xulgvec)
    );
    
    std::vector<unsigned long> added_idx {9UL, 10UL, 11UL, 12UL};

    // df.append_index<std::vector<unsigned long>::iterator const&>(hmdf::Index2D<std::vector<unsigned long>::iterator const&>{added_idx.begin() , added_idx.end()});

    df.append_index<CLDataFrameIdxItType const&>({added_idx.begin(), added_idx.end()});
    df.write<std::ostream, int, double, std::string, unsigned long>(std::cout);
}


GTEST_TEST(DFAppendColTests, AppendIdxSingle) {
    CLDataFrame df;
    std::vector<int> intvec {1, 2, 3, 4, 5};
    std::vector<double> dblvec {1.2345, 2.2345, 3.2345, 4.2345, 5.2345};
    std::vector<double> dblvec2 {0.998, 0.3456, 0.056, 0.15678, 0.00345, 0.923, 0.06743, 0.1 };
    std::vector<std::string> strvec {"Col_name", "Col_name", "Col_name", "Col_name", "Col_name"};

    std::vector<unsigned long> ulgvec {1UL, 2UL, 3UL, 4UL, 5UL, 8UL, 7UL, 6UL};
    auto xulgvec {ulgvec};

    auto rc = df.load_data(
        std::move(ulgvec),
        std::make_pair("int_col", intvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("dbl_col2", dblvec2),
        std::make_pair("str_col", strvec),
        std::make_pair("ul_col", xulgvec)
    );
    df.append_index(9UL);
    df.write<std::ostream, int, double, std::string, unsigned long>(std::cout);
}


