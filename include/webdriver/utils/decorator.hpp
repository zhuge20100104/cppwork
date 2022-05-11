#ifndef _FREDRIC_DECORATOR_HPP_
#define _FREDRIC_DECORATOR_HPP_


#include <chrono>
#include <functional>
#include <iostream>

#include <webdriverxx/webdriverxx.h>

#include "webdriver/utils/beans.h"
#include "webdriver/test_cfg.h"

#include "glog/logging.h"

using namespace webdriverxx;

template<typename R, typename T, typename Func, typename ... Args>
Result<R> decorator_run(const T& obj, Func func, Args ... args) {
        try {
            WaitUntil([&obj]() {
                auto res = obj.template Eval<std::string>("return document.readyState", {});
                if(res == "complete") {
                    LOG(ERROR) << "Load result completed.." << "\n";
                    return true;
                } else {
                    return false;
                }
            }, page_load_timeout, page_check_interval);

            auto invoke_func = std::bind(func, obj, args...);
            auto res = invoke_func();
            return Result<R>{true, std::move(res)};
        } catch(std::exception const &ex) {
            LOG(ERROR) << ex.what() << "\n";
            return Result<R>{false, R()};
        }
}

#define element_finder_func(driver, func, by) decorator_run<Element>(driver, func, by)
#define elements_finder_func(driver, func, by) decorator_run<std::vector<Element>>(driver, func, by)

#define element_finder(driver, by) element_finder_func(driver, &WebDriver::FindElement, by)
#define element_finder_ele(driver, by)  element_finder(driver, by).obj
#define element_exists(driver, by)  element_finder(driver, by).res

#define elements_finder(driver, by) elements_finder_func(driver, &WebDriver::FindElements, by)
#define elements_finder_eles(driver, by)  elements_finder(driver, by).obj
#define elements_exists(driver, by)  elements_finder(driver, by).res


#define screenshot_saver(driver, file_name) decorator_run<int>(driver, &WebDriver::GetScreenshotAsFile, file_name)

#endif