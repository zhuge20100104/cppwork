#include "csv/csv_util.h"
#include "http/http_util.h"

#include <iostream>

const std::string IMAGE_PATH = "./images";


bool test_a_image(std::string host, std::string path, std::string result_name) {
   
    std::string final_path = "/img/" +  path;

    std::string final_result_name = IMAGE_PATH + "/"+ result_name;

    bool res = HttpUtil::get_file(host, final_path , final_result_name);
    if(!res) {
        std::cerr << "Download [ https://" << host << final_path <<  "] failed" << std::endl;
        return false;
    } else {
        std::cout << "Download [ https://" << host << final_path << "] successful" << std::endl;
        return true;
    }
}


int main(int argc, char* argv[]) {
    std::string host = "static-s.aa-cdn.net";

    std::size_t index = 0;
    auto res = CSVUtil::read_csv("./among-gp.csv", "PRODUCT_KEY", "OLD_VALUE", "NEW_VALUE", "CHANGE_TIME");
    for(auto && ele: res) {
        std::cout << "=========================================================" << std::endl;
        std::cout << ele.product_id << "\t" << ele.old_url << "\t" << ele.new_url << "\t" << ele.date << std::endl;
        test_a_image(host, ele.old_url, std::to_string(index) + "_old.png");
        test_a_image(host, ele.new_url, std::to_string(index) + "_new.png");
        ++index;
    }

    return 0;
}