#include "tasks/task_reader.h"
#include "tasks/task_launcher.h"
#include "tasks/url_parse.h"

#include <gtest/gtest.h>

std::string task_file_path = "../../cases/single_test.json";

GTEST_TEST(TasksTests, ReaderTest) {
    task t {10, 5};
    auto reader = task_reader(t);
    auto task_res_str = reader.parse_tasks(task_file_path);
    ASSERT_NE("", task_res_str);
}

GTEST_TEST(TasksTests, LauncherDumpRequests) {
    auto task_info = R"({"requests":{"single":{"BingRequest":{"body":"","headers":{"Content-Type":"text/html"},"method":"GET","url":"https://cn.bing.com"}}},"stress_hold_on_time":30,"thread_count":50})";

    task_launcher launcher {task_info};
    launcher.dump_requests();
    ASSERT_TRUE(true);
}

GTEST_TEST(TasksTests, UrlParseTest) {
    url_parse parse_ {"https://cn.bing.com"};
    parse_.parse_host_and_path();
    std::cerr << "URL: " << parse_.get_host() << std::endl;
    std::cerr << "Path: " <<  parse_.get_path() << std::endl;
    ASSERT_EQ("cn.bing.com", parse_.get_host());
    ASSERT_EQ("", parse_.get_path());

    url_parse parse1_ {"https://www.baidu.com/"};
    parse1_.parse_host_and_path();
    std::cerr << "URL: " << parse1_.get_host() << std::endl;
    std::cerr << "Path: " <<  parse1_.get_path() << std::endl;
    ASSERT_EQ("www.baidu.com", parse1_.get_host());
    ASSERT_EQ("/", parse1_.get_path());


    url_parse parse2_ {"https://www.appannie.com/v2/query"};
    parse2_.parse_host_and_path();
    std::cerr << "URL: " << parse2_.get_host() << std::endl;
    std::cerr << "Path: " <<  parse2_.get_path() << std::endl;
    ASSERT_EQ("www.appannie.com", parse2_.get_host());
    ASSERT_EQ("/v2/query", parse2_.get_path());
}

GTEST_TEST(TasksTests, GetPerThreadSleepMills) {
    auto task_info = R"({"requests":{"single":{"BingRequest":{"body":"","headers":{"Content-Type":"text/html"},"method":"GET","url":"https://cn.bing.com"}}},"stress_hold_on_time":30,"thread_count":50})";
    
    task_launcher launcher_{task_info};
    auto per_mills = launcher_.get_per_thread_sleep_mills(30, 5);

    ASSERT_EQ(166, per_mills);

    auto per_mills_zero = launcher_.get_per_thread_sleep_mills(30, 0);
    ASSERT_EQ(0, per_mills_zero);
}


GTEST_TEST(TasksTests, TestRunOneRequest) {
    auto task_info = R"({"requests":{"single":{"BingRequest":{"body":"","headers":{"Content-Type":"text/html"},"method":"GET","url":"https://cn.bing.com"}}},"stress_hold_on_time":30,"thread_count":50})";
    task_launcher launcher_{task_info};
    request req_value {"https://cn.bing.com", request::request_method::GET, "", {{"Content-Type", "text/html"}}};
    req_result req_res{0, false};
    launcher_.run_a_request(req_value, req_res);
    ASSERT_TRUE(!req_res.is_failed);
}

GTEST_TEST(TasksTests, TestRunAndGetResults) {
    auto task_info = R"({"requests":{"single":{"BingRequest":{"body":"","headers":{"Content-Type":"text/html"},"method":"GET","url":"https://cn.bing.com"}}},"stress_hold_on_time":0,"thread_count":50})";
    task_launcher launcher_{task_info};
    launcher_.dump_requests();
    launcher_.run();
    auto results_str = launcher_.dump_results();
    std::cerr << results_str << std::endl;
    ASSERT_TRUE(results_str.find("single") != std::string::npos);
}

