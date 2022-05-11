#include "images_timeline/images_.h"

#include <algorithm>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <functional>

#include "http/http_util.h"
#include "utils/cfg_reader.h"
#include "images_timeline/decorator.hpp"
#include "images_timeline/task_manager.hpp"
#include "img_util/img_util.h"
#include "json/json.hpp"
#include "pystring/pystring.h"
#include "sf_db2/sf_db2.h"

using json = nlohmann::json;

const int BatchSize = 2;
const std::string ConnStr = "dsn=product_odbc;pwd=Lily870104";

const std::string ImagePath = "../images";
const std::string CfgPath = "../../conf/data.conf";
const std::string CdnHost = "static-s.aa-cdn.net";


screenshots_value_type parse_screenshot_val(const std::string& value) {
    screenshots_value_type ret_val{};

    auto json_value = json::parse(value);
    // 使用 nlohmann::json 库解析json对象，拿取对象中的URL
    // 对象格式 {"default":
    // ["gp/20600013289355/OpozImyAlqDxklfG2v3MSHpUfWxeCUIhz2nqJf_g9knQU2cd9o4vY7OSSUnM7ElzBDyI"]}
    for (auto &&image_it = json_value.begin(), end = json_value.end();
         image_it != end; ++image_it) {
        auto key_ = image_it.key();
        std::vector<std::string> images_{};

        auto image_vals_ = image_it.value();
        for (auto image : image_vals_) {
            images_.emplace_back(std::move(image.get<std::string>()));
        }

        ret_val[key_] = std::move(images_);
    }
    return std::move(ret_val);
}

meta_type parse_meta_val(const std::string& value) {
    auto meta_value = json::parse(value);
    meta_type ret_val;
    for (auto &&meta_it = meta_value.begin(), end = meta_value.end();
         meta_it != end; ++meta_it) {
        auto key_ = meta_it.key();
        auto val_ = meta_it.value().get<std::string>();
        ret_val[key_] = val_;
    }
    return std::move(ret_val);
}

std::vector<screenshots> get_screenshots_from_db() {
    std::vector<screenshots> res_eles{};
    std::map<std::string, std::string> cfg_;
    bool read_res = cfg_reader::read_file(CfgPath, cfg_);
    
    if(!read_res) {
        std::cerr << "Read config file failed" << std::endl;
        return res_eles;
    }

    auto date_ =  cfg_["date"];

    auto conn_str = ConnStr;
    std::stringstream ss;
    ss <<  R"(select product_key, old_value, new_value, meta, change_time
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_localized_event_service_v1_cluster_by_product_key
    where market_code='apple-store' 
    and event_type_name='screenshot_change'
    and change_time=')";
    ss << date_;
    ss << "' ";
    ss << "and meta is not null  order by change_time desc limit 10;";
    auto raw_query = ss.str();

    std::cerr << raw_query << std::endl;

    sf_connection sf{conn_str};
    auto res = sf.exec_raw_query(raw_query);
    int ele_size = res.affected_rows();
    const auto columns = res.columns();

    const std::string null_value = "null";
    while (res.next()) {
        auto const product_id_ = res.get<std::string>(0, null_value);
        auto const old_json_str = res.get<std::string>(1, null_value);
        auto const new_json_str = res.get<std::string>(2, null_value);
        auto const meta_str = res.get<std::string>(3, null_value);
        auto const change_time = res.get<std::string>(4, null_value);

        auto old_value = parse_screenshot_val(old_json_str);
        auto new_value = parse_screenshot_val(new_json_str);
        auto meta_value = parse_meta_val(meta_str);
        screenshots screenshots_{product_id_, old_value, new_value, meta_value,
                                 change_time};
        res_eles.emplace_back(std::move(screenshots_));
    }
    return std::move(res_eles);
}

bool test_a_image(const std::string& host, const std::string& path) {
    std::string final_path = "/img/" + path;
    std::string result_name = path;
    // 原先URL path替换 "/"为 "_"，作为文件名，就不用自己生成UUID了
    auto tmp_result_name = pystring::replace(result_name, "/", "_");
    std::string final_result_name = ImagePath + "/" + tmp_result_name + ".png";
    bool res = HttpUtil::get_file(host, final_path, final_result_name);
    if (!res) {
        return false;
    } else {
        return true;
    }
}

template <typename T>
void test_one_screenshots_value(decorator<T> image_test_func,
                                const screenshots_value_type& screenshot_values,
                                int& cant_be_accessed_count) {
    for (auto&& device_obj : screenshot_values) {
        auto images = device_obj.second;
        for (auto& image_ : images) {
            auto success = image_test_func(CdnHost, image_);
            if (!success) {
                std::cerr << "Download [ https://" << CdnHost << "/img/"
                          << image_ << "] failed" << std::endl;
                ++cant_be_accessed_count;
            }
        }
    }
}

void download_a_batch(const std::vector<screenshots>& screenshots_,
                      int& cant_be_accessed_count) {
    auto image_test_func = make_decorator(test_a_image);
    for (auto&& screenshot_ : screenshots_) {
        auto old_values = screenshot_.old_value;
        auto new_values = screenshot_.new_value;
        test_one_screenshots_value(image_test_func, old_values,
                                   cant_be_accessed_count);
        test_one_screenshots_value(image_test_func, new_values,
                                   cant_be_accessed_count);
    }
}

bool test_all_images_can_be_accessed() {
    auto screenshots_ = get_screenshots_from_db();
    std::cout << "Total screenshots element count: " << screenshots_.size()
              << std::endl;

    // 按BatchSize大小进行分批，放进subVector中
    task_manager<screenshots> manager_{screenshots_, BatchSize};
    manager_.divide_elements_to_batches();
    manager_.start_thread_pool_and_run_tasks(download_a_batch);
    int total_failed_num = manager_.collect_failed_count();

    std::cout << "Total failed nums: [" << total_failed_num << "]" << std::endl;
    return total_failed_num == 0;
}

bool compare_a_screenshot_list(const screenshots& screenshots_) {
    auto meta_ = screenshots_.meta;
    auto old_value_ = screenshots_.old_value;
    auto new_value_ = screenshots_.new_value;

    bool all_match {true};

    for (auto&& meta_ele : meta_) {
        auto compare_key_prefix = meta_ele.first;
        // The compared meta value
        auto compare_val = meta_ele.second;

        bool is_match {false};
        for (auto&& old_value_ele : old_value_) {
            auto real_key = old_value_ele.first;
            // Matched the compare key prefix
            if (pystring::startswith(real_key, compare_key_prefix)) {
                auto old_value_to_cmp = old_value_ele.second;
                auto new_value_to_cmp = new_value_[real_key];
                int old_size = old_value_to_cmp.size();
                int new_size = new_value_to_cmp.size();
                int min_size = old_size < new_size ? old_size : new_size;

                // The actual compared meta value.
                std::string act_compare_val{};

                for (int i = 0; i < min_size; ++i) {
                    auto old_img_url = old_value_to_cmp[i];
                    auto new_img_url = new_value_to_cmp[i];
                    auto old_img_path =
                        ImagePath + "/" +
                        pystring::replace(old_img_url, "/", "_") + ".png";
                    auto new_img_path =
                        ImagePath + "/" +
                        pystring::replace(new_img_url, "/", "_") + ".png";
                    auto res =
                        ImageUtil::compare_equal(old_img_path, new_img_path);
                    // equal true, no change, add zero
                    if (res) {
                        act_compare_val += "0";
                    } else {
                        act_compare_val += "1";
                    }
                }

                if (pystring::startswith(compare_val, act_compare_val)) {
                    is_match = true;
                    break;
                } else {
                    std::cerr << "Real key: " << real_key << std::endl;
                    std::cerr << "Compare Value: " << compare_val << std::endl;
                    std::cerr << "Actual Compare Value: " << act_compare_val << std::endl;
                }
            }
        }

        if(!is_match) {
            std::cerr << compare_key_prefix << " is not match" << std::endl;
            all_match = false;
            break;
        }
    }

    return all_match;
}

void compare_a_batch(const std::vector<screenshots>& screenshots_,
                     int& compare_failed_count) {
    for (auto&& screenshot_ : screenshots_) {
        bool ret = compare_a_screenshot_list(screenshot_);
        if (!ret) {
            std::cerr << "Failed Screenshot: " << screenshot_;
            ++compare_failed_count;
        }
    }
}

bool test_meta_is_correct() {
    auto screenshots_ = get_screenshots_from_db();
    std::cout << "Total screenshots element count: " << screenshots_.size()
              << std::endl;

    std::vector<std::vector<screenshots>> sub_eles;

    // 按BatchSize大小进行分批，放进subVector中
    task_manager<screenshots> manager_{screenshots_, BatchSize};
    manager_.divide_elements_to_batches();
    manager_.start_thread_pool_and_run_tasks(compare_a_batch);
    int total_failed_num = manager_.collect_failed_count();

    std::cout << "Total failed nums: [" << total_failed_num << "]" << std::endl;
    return total_failed_num == 0;
}

std::vector<icon_url> get_icon_url_from_db() {
    auto conn_str = ConnStr;
    auto raw_query =
        R"(select distinct product_key, old_value, new_value, change_time
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_localized_event_service_v1_cluster_by_product_key
    where market_code='apple-store' 
    and event_type_name='artwork_url_change' 
    and old_value is not null and new_value is not null
    order by change_time desc limit 100;)";

    sf_connection sf{conn_str};
    auto res = sf.exec_raw_query(raw_query);
    int ele_size = res.affected_rows();
    const auto columns = res.columns();
    std::vector<icon_url> res_eles{};

    const std::string null_value = "null";
    while (res.next()) {
        auto const product_id_ = res.get<std::string>(0, null_value);
        auto const old_value = res.get<std::string>(1, null_value);
        auto const new_value = res.get<std::string>(2, null_value);
        auto const change_time = res.get<std::string>(3, null_value);
        icon_url icon_url_{product_id_, old_value, new_value, change_time};
        res_eles.emplace_back(std::move(icon_url_));
    }
    return std::move(res_eles);
}

template <typename T>
void test_one_icon_value(decorator<T> image_test_func,
                         const std::string& url_value,
                         int& cant_be_accessed_count) {
    auto success = image_test_func(CdnHost, url_value);
    if (!success) {
        std::cerr << "Download [ https://" << CdnHost << "/img/" << url_value
                  << "] failed" << std::endl;
        ++cant_be_accessed_count;
    }
}
void download_a_batch_of_icons(const std::vector<icon_url>& icon_urls_,
                               int& cant_be_accessed_count) {
    auto image_test_func = make_decorator(test_a_image);
    for (auto&& icon_url_ : icon_urls_) {
        auto old_value = icon_url_.old_url;
        auto new_value = icon_url_.new_url;
        test_one_icon_value(image_test_func, old_value, cant_be_accessed_count);
        test_one_icon_value(image_test_func, new_value, cant_be_accessed_count);
    }
}

bool test_all_icons_can_be_accessed() {
    auto icon_urls_ = get_icon_url_from_db();
    std::cout << "Total icon urls element count: " << icon_urls_.size()
              << std::endl;

    // 按BatchSize大小进行分批，放进subVector中
    task_manager<icon_url> manager_{icon_urls_, BatchSize};
    manager_.divide_elements_to_batches();
    manager_.start_thread_pool_and_run_tasks(download_a_batch_of_icons);
    int total_failed_num = manager_.collect_failed_count();

    std::cout << "Total failed nums: [" << total_failed_num << "]" << std::endl;
    return total_failed_num == 0;
}

bool compare_a_icon_pair(const icon_url& icon_url_) {
    auto old_img_url = icon_url_.old_url;
    auto new_img_url = icon_url_.new_url;

    auto old_img_path =
        ImagePath + "/" + pystring::replace(old_img_url, "/", "_") + ".png";
    auto new_img_path =
        ImagePath + "/" + pystring::replace(new_img_url, "/", "_") + ".png";
    auto res = ImageUtil::compare_equal(old_img_path, new_img_path);
    return !res;
}

void compare_a_batch_icons(const std::vector<icon_url>& icon_urls_,
                           int& compare_failed_count) {
    for (auto&& icon_url_ : icon_urls_) {
        bool ret = compare_a_icon_pair(icon_url_);

        if (!ret) {
            std::cerr << "Icons are equal: " << std::endl;
            std::cerr << icon_url_;
            std::cerr << std::endl;
            ++compare_failed_count;
        }
    }
}

bool test_icons_are_correct() {
    auto icon_urls_ = get_icon_url_from_db();
    std::cout << "Total icon_urls element count: " << icon_urls_.size()
              << std::endl;

    std::vector<std::vector<icon_url>> sub_eles;

    // 按BatchSize大小进行分批，放进subVector中
    task_manager<icon_url> manager_{icon_urls_, BatchSize};
    manager_.divide_elements_to_batches();
    manager_.start_thread_pool_and_run_tasks(compare_a_batch_icons);
    int total_failed_num = manager_.collect_failed_count();

    std::cout << "Total failed nums: [" << total_failed_num << "]" << std::endl;
    return total_failed_num == 0;
}