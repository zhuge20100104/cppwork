#include "df/df.h"
#include "death_handler/death_handler.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "json/json.hpp"

#include <fstream>
#include <sstream>

using json = nlohmann::json;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;
    
    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

static std::vector<std::string> add_columns(
    CLDataFrame::IndexVecType::const_iterator idx_begin,
    CLDataFrame::IndexVecType::const_iterator idx_end,
    std::vector<double>::const_iterator b_citer1,
    std::vector<double>::const_iterator e_citer1,
    std::vector<double>::const_iterator b_citer2,
    std::vector<double>::const_iterator e_citer2,
    std::vector<std::string>::const_iterator b_citer3,
    std::vector<std::string>::const_iterator e_citer3
) {
    std::size_t const col_s = std::min({std::distance(b_citer1, e_citer1), std::distance(b_citer2, e_citer2), std::distance(b_citer3, e_citer3)});

    std::vector<std::string> result {col_s};

    for(std::size_t i=0; i<col_s; ++i) {
        result[i] = *(b_citer3+i) + std::to_string(*(b_citer1+i) + *(b_citer2+i));
    }
    return result;
}

GTEST_TEST(DFConsolidateTests, SelfConsolidateCol) {
    LOG(INFO) << "\nTesting consolidate()...\n";
    CLDataFrame df;

    std::vector<unsigned long>  idxvec = {
        1UL, 2UL, 3UL, 10UL, 5UL, 7UL, 8UL, 12UL, 9UL, 12UL, 10UL, 13UL, 10UL, 15UL, 14UL
    };
    std::vector<double>         dblvec = {
        0.0, 15.0, 14.0, 2.0, 1.0, 12.0, 11.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 9.0, 10.0
    };
    std::vector<double>         dblvec2 = {
        100.0, 101.0, 102.0, 103.0, 104.0, 105.0, 106.55, 107.34, 1.8, 111.0, 112.0, 113.0, 114.0, 115.0, 116.0
    };
    std::vector<int>            intvec = { 1, 2, 3, 4, 5, 8, 6, 7, 11, 14, 9 };
    std::vector<std::string>    strvec = {
        "zz", "bb", "cc", "ww", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo"
    };

    df.load_data(
        std::move(idxvec),
        std::make_pair("dbl_col", dblvec),
        std::make_pair("dbl_col_2", dblvec2), 
        std::make_pair("str_col", strvec)
    );

    df.load_column("int_col", std::move(intvec), hmdf::nan_policy::dont_pad_with_nans);

    df.consolidate<double, double, std::string, std::string>(
        "dbl_col", "dbl_col_2", "str_col", "new_str_col", add_columns, /*delete_old_cols*/true
    );

    assert(!df.has_column("dbl_col"));
    assert(!df.has_column("dbl_col2"));
    assert(!df.has_column("str_col"));

    assert(df.has_column("new_str_col"));

    auto const& new_str_col = df.get_column<std::string>("new_str_col");
    
    const std::vector<std::string> actual = {
        "zz100.000000", "bb116.000000", "cc116.000000", "ww105.000000", "ee105.000000", "ff117.000000", "gg117.550000", "hh115.340000",
        "ii8.800000", "jj117.000000", "kk117.000000", "ll117.000000", "mm117.000000", "nn124.000000", "oo126.000000"
    };

    for(std::size_t idx=0; idx<actual.size(); ++idx) {
        assert(new_str_col[idx] == actual[idx]);
    }
}