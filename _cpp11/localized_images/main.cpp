#include "http/http_util.h"
#include "json/json.hpp"
#include "pystring/pystring.h"
#include "sf_db2/sf_db2.h"

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include <vector>


using json = nlohmann::json;

struct image_ele {
    std::string product_id;
    std::string image_path;
};

const int BatchSize = 1000;
const std::string ConnStr = "dsn=product_odbc;pwd=Lily870104";
const std::string ImagePath = "./images";
const std::string CdnHost = "static-s.aa-cdn.net";

std::vector<image_ele> get_images_from_db() {
    auto conn_str = ConnStr;
    auto raw_query =
        R"(select product_key, screenshots_md5 
        from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.DIM_PRODUCT_LOCALIZED_DETAIL_V1_CLUSTER_BY_PRODUCT_KEY
        limit 2000;)";

    sf_connection sf{conn_str};
    auto res = sf.exec_raw_query(raw_query);
    int ele_size = res.affected_rows();
    const auto columns = res.columns();
    std::vector<image_ele> res_eles{};

    const std::string null_value = "null";
    while (res.next()) {
        auto const product_id_ = res.get<std::string>(0, null_value);
        auto const image_json_ = res.get<std::string>(1, null_value);
        auto image_obj = json::parse(image_json_);
        // 使用 nlohmann::json 库解析json对象，拿取对象中的URL
        // 对象格式 {"default":
        // ["gp/20600013289355/OpozImyAlqDxklfG2v3MSHpUfWxeCUIhz2nqJf_g9knQU2cd9o4vY7OSSUnM7ElzBDyI"]}
        for (auto &&image_it = image_obj.begin(), end = image_obj.end();
             image_it != end; ++image_it) {
            auto img_list = *image_it;
            for (auto&& image_url : img_list) {
                image_ele ele{product_id_, image_url};
                res_eles.emplace_back(std::move(ele));
            }
        }
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
        std::cerr << "Download [ https://" << host << final_path << "] failed"
                  << std::endl;
        return false;
    } else {
        return true;
    }
}

void download_a_batch(const std::vector<image_ele>& sub_vec) {
    for (auto&& ele : sub_vec) {
        test_a_image(CdnHost, ele.image_path);
    }
}

int main(int argc, char* argv[]) {
    // 从DB获取图片信息
    auto res = get_images_from_db();

    std::cout << "Total image count: " << res.size() << std::endl;

    // 按BatchSize大小进行分批，放进subVector中
    std::size_t batches = res.size() / BatchSize + 1;
    std::vector<std::vector<image_ele>> sub_eles;

    for (int i = 0; i < batches; ++i) {
        std::vector<image_ele> sub_ele{};
        if (i + 1 < batches) {
            for (int j = 0; j < BatchSize; ++j) {
                sub_ele.emplace_back(std::move(res[i * BatchSize + j]));
            }
        } else {
            for (int j = 0; j < res.size() % BatchSize; ++j) {
                sub_ele.emplace_back(std::move(res[i * BatchSize + j]));
            }
        }
        sub_eles.emplace_back(std::move(sub_ele));
    }

    // 使用asio thread_pool启动线程池，运行子任务
    boost::asio::thread_pool pool{batches};

    for (int i = 0; i < sub_eles.size(); ++i) {
        boost::asio::post(pool,
                          std::bind(download_a_batch, std::ref(sub_eles[i])));
    }

    pool.join();
    return 0;
}