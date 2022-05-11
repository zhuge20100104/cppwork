#include <webdriverxx/webdriverxx.h>

#include "pystring/pystring.h"
#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "webdriver/utils/decorator.hpp"

#include <chrono>
#include <thread>
#include <pystring/pystring.h>
#include <gtest/gtest.h>

using namespace webdriverxx;

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

WebDriver initWebDriver() {
    auto caps = Capabilities();
    caps.SetVersion("93.0.4577.63");
    caps.SetBrowserName(browser::Chrome);
    caps.SetPlatform(platform::Any);
    WebDriver driver = Start(Chrome(caps));
    return std::move(driver);
}

GTEST_TEST(WdTests, TestBaidu) {
    auto driver = initWebDriver();
    driver.Navigate("https://www.baidu.com");
    auto kw = driver.FindElement(ById("kw"));
    kw.SendKeys("Hello");
    auto su = driver.FindElement(ById("su"));
    su.Click();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto source = driver.GetPageSource();
    auto source_lower = pystring::lower(source);
    ASSERT_TRUE(source_lower.find("hello") != std::string::npos);
}

GTEST_TEST(WdTests, TestEventBubble) {
    auto driver = initWebDriver();
    driver.Navigate("https://www.appannie.com/event_bubbles/timeline/popup/?branding=IN&current_date=1622419200000&start_date=2021-04-01&end_date=2021-08-31&unified_apps=1000600000803861,1000600000509568,1000600000575007,1000600000000441&filter_unified_market=ios,gp");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    element_finder_ele(driver, ByName("username")).SendKeys("fzhu@appannie.com");
    driver.FindElement(ByXPath(R"(//input[@placeholder="Password"])")).SendKeys("Lily!870104");
    driver.FindElement(ByXPath(R"(//button[@type="submit"])")).Click();

    std::this_thread::sleep_for(std::chrono::seconds(20));
    auto ele = driver.FindElement(ByXPath(R"(//div[@class="event-icon-container"])"));
    ASSERT_TRUE(ele.IsDisplayed());
}


GTEST_TEST(WdTests, TestAppSummaryLocalized) {
    auto driver = initWebDriver();
    driver.Navigate("https://www.appannie.com/apps/ios/app/284882215/details?date=!(%272021-07-04%27,%272021-09-25%27)&granularity=daily&country_code=CN");
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    driver.FindElement(ByName("username")).SendKeys("fzhu@appannie.com");
    driver.FindElement(ByXPath(R"(//input[@placeholder="Password"])")).SendKeys("Lily!870104");
    driver.FindElement(ByXPath(R"(//button[@type="submit"])")).Click();

    std::this_thread::sleep_for(std::chrono::seconds(20));
    auto ele = driver.FindElement(ByXPath(R"(//div[text()="China"])"));
    ASSERT_TRUE(ele.IsDisplayed());
}