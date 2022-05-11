#include <glog/logging.h>
#include <gtest/gtest.h>

#include "html/html_.h"
#include "death_handler/death_handler.h"
#include "df/df.h"
#include "json/json.hpp"
#include "pystring/pystring.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 1;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

GTEST_TEST(HtmlParserTest, TestParseFile) {
    std::ifstream ifs {"../data/bookmarks_11_11_21.html"};
    auto doc = Html::get_html_doc(ifs);
    auto eles = doc.getElementsByTagName("a");
    auto it = eles.begin();
    auto attr = it->getAttribute("href");
    LOG(WARNING) << attr;
    LOG(WARNING) << it->getTextContent();
}

GTEST_TEST(HtmlParserTest, TestParseStr) {
    std::string html_str = R"(<div name="my">a &le; b</div><span name="my">qwq</span>)";
    auto doc = Html::get_html_doc(html_str);
    auto eles = doc.getElementsByName("my");
    for(auto&& ele: eles) {
        LOG(WARNING) << ele.getTextContent();
    }
}