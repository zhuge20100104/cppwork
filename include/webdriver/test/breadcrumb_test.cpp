#include <glog/logging.h>
#include <gtest/gtest.h>
#include <webdriverxx/webdriverxx.h>

#include <fstream>
#include <chrono>
#include <thread>

#include <boost/type_index.hpp>
#include "death_handler/death_handler.h"
#include "html/html_.h"
#include "pystring/pystring.h"
#include "webdriver/utils/beans.h"
#include "webdriver/utils/decorator.hpp"
#include "webdriver/test_cfg.h"


using namespace webdriverxx;

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

class BreadCrumbTests : public testing::Test {
   protected:
    virtual void SetUp() {
        std::ifstream ifs{test_data_path};
        auto doc = Html::get_html_doc(ifs);
        auto eles = doc.getElementsByTagName("a");
        for (auto&& ele : eles) {
            auto url = (std::string)ele.getAttribute("href");
            auto name = (std::string)ele.getTextContent();
            LinkItem item{name, url};
            auto index = pystring::find(url, test_host_name);
            if (index >= 0) {
                link_items_.emplace_back(std::move(item));
            }
        }

        for (auto&& item : link_items_) {
            LOG(WARNING) << item.name;
            LOG(WARNING) << item.url;
            LOG(WARNING) << "\n";
        }
    }

    void saveScreenshot(const WebDriver& driver, const std::string& file_name, const int& i) {
        
        std::stringstream ss;
        ss << screenshot_file_path << i << "_" <<file_name << ".jpg";
        auto screen_shot_res = screenshot_saver(driver, ss.str());
        if(screen_shot_res.res) {
            LOG(WARNING) << "Get screenshot ok " << " code: " << screen_shot_res.obj  << "\n"; 
        }
    }

    WebDriver initWebDriver() {
        auto caps = Capabilities();
        caps.SetVersion("93.0.4577.63");
        caps.SetBrowserName(browser::Chrome);
        caps.SetPlatform(platform::Any);

        auto options_ = ChromeOptions();
        options_.GetArgs().emplace_back("--force-device-scale-factor=1");
        auto chrome_ = Chrome(caps);
        chrome_.SetChromeOptions(options_);

        WebDriver driver = Start(chrome_);
        return std::move(driver);
    }

    void loginToPage(WebDriver& driver, const std::string& url) {
        driver.Navigate(url.c_str());
        std::this_thread::sleep_for(std::chrono::seconds(1));

        driver.FindElement(ByName("username")).SendKeys("fzhu@appannie.com");
        driver.FindElement(ByXPath(R"(//input[@placeholder="Password"])"))
            .SendKeys("Lily!870104");
        driver.FindElement(ByXPath(R"(//button[@type="submit"])")).Click();

        std::this_thread::sleep_for(std::chrono::seconds(20));
    }
    virtual void TearDown() {}

    std::vector<LinkItem> link_items_;
};

TEST_F(BreadCrumbTests, TestWebSites) {
    auto driver = initWebDriver();
    int i = 0;
    bool is_case_pass = true;
    for (auto&& item : link_items_) {
        if(i==0) {
            loginToPage(driver, item.url);
        }else {
            driver.Navigate(item.url);
            auto disable_index = pystring::find(item.name, "disable");
            auto hidden_index = pystring::find(item.name, "hidden");

            if(disable_index >= 0 || hidden_index >= 0) {
                saveScreenshot(driver, item.name, i);
                auto disable_xpath = R"(//h1[contains(@class, "Typography__Title-sc-h8dyzi-0")])";
                auto ele = element_finder(driver, ByXPath(disable_xpath));
                if(ele.res) {
                    auto _404_text = ele.obj.GetText();
                    if(_404_text != "Oops! 404") {
                            LOG(ERROR) << "Url disabled is not 404 status [" << item.name <<  "] [" << item.url << "]" << "\n";
                            is_case_pass = false;
                    }
                }else {
                    LOG(ERROR) << "Url disabled is not 404 status [" << item.name <<  "] [" << item.url << "]" << "\n";
                    is_case_pass = false;
                }
            }else {
                saveScreenshot(driver, item.name, i);
                auto breadcrumb = element_finder(driver, ByXPath("//nav[@aria-label='Breadcrumb']"));
                if(breadcrumb.res) {
                    if(!breadcrumb.obj.IsDisplayed()) {
                        is_case_pass = false;
                        LOG(ERROR) << "Url breadcrumb is not 200 status [" << item.name << "] [" << item.url << "]" << "\n";
                    }
                } else {
                    LOG(ERROR) << "Url breadcrumb is not 200 status [" << item.name << "] [" << item.url << "]" << "\n";
                    is_case_pass = false;
                }
            }       
        }
        ++i;
    }

    ASSERT_TRUE(is_case_pass);
}

TEST_F(BreadCrumbTests, TestDisabledXPath) {
    auto driver = initWebDriver();
    loginToPage(driver, "https://tai4.appannie.com/apps/google-play/app/20600012193818/details");
    auto disable_xpath = R"(//h1[contains(@class, "Typography__Title-sc-h8dyzi-0")])";   
    auto ele_res = element_finder(driver, ByXPath(disable_xpath));

    ASSERT_TRUE(ele_res.obj.IsDisplayed());
}

TEST_F(BreadCrumbTests, TestSaveScreenshot) {
     auto driver = initWebDriver();
     driver.Get("https://cn.bing.com");
     
     std::this_thread::sleep_for(std::chrono::seconds(4));
     auto divs = elements_finder_eles(driver, ByTag("div"));
     LOG(WARNING) << "Div size: " << divs.size() << "\n";
     saveScreenshot(driver, "hehe", 1);
}


