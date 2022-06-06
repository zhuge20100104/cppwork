
#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>
#include "utils/conv_util.h"
#include "utils/import_util.h"
#include "utils/zepplin_mig_cfg.h"

#include <gtest/gtest.h>
#include "df/df.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

GTEST_TEST(ConvNB2PyTests, NB2PyLocal) {
    auto res = ConvUtil::get_all_note_books(zepplin_js_path, DataSource::LOCAL);
    auto conv_res = ConvUtil::conv_notebook_2_py(res);
    ASSERT_TRUE(conv_res);
}

GTEST_TEST(ConvNB2PyTests, NB2IPyNBLocal) {
    auto res = ConvUtil::get_all_note_books(zepplin_js_path, DataSource::LOCAL);
    auto conv_res = ConvUtil::conv_notebook_2_ipynb(res);
    ASSERT_TRUE(conv_res);
}

GTEST_TEST(ConvNB2PyTests, NB2PyDB) {
    auto res = ConvUtil::get_all_note_books(zepplin_js_path, DataSource::DB);
    auto conv_res = ConvUtil::conv_notebook_2_py(res);
    ASSERT_TRUE(conv_res);
}

GTEST_TEST(ConvNB2PyTests, NB2IPyNBDB) {
    auto res = ConvUtil::get_all_note_books(zepplin_js_path, DataSource::DB);
    auto conv_res = ConvUtil::conv_notebook_2_ipynb(res);
    ASSERT_TRUE(conv_res);
}

GTEST_TEST(ConvNB2PyTests, IPyNBImport) {
    auto conv_res = ImportUtil::import_note_books(ipynbs_test_path);
    ASSERT_TRUE(conv_res);
}