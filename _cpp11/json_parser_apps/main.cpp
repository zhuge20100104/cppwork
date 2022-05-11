#include <boost/foreach.hpp>
#include <boost/version.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string JsonName = "../single_data.json";

struct Result {
    int64_t featured_category_key;
    int64_t collection_type_code;
    int64_t story_id;
    std::string story_label;
    std::string item_type;
    std::string item_note;
    std::string story_note;
    int64_t product_key;
};

int main(int argc, char* argv[]) {

    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
    
    std::vector<Result> results;
    try {
        std::ifstream t(JsonName);
        if (!t) {
            std::cerr << "Can't open file" << std::endl;
            return EXIT_FAILURE;
        }
        std::stringstream ss;
        ss << t.rdbuf();

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);

        for (const auto& data : pt) {
            auto first_datas = data.second.get_child("data");
            for (const auto& first_data : first_datas) {
                int64_t featured_category_key{0};
                featured_category_key =
                    strtoll(first_data.second.get_child("id").data().c_str(),
                            nullptr, 10);

                auto second_datas = first_data.second.get_child("relationships")
                                        .get_child("tabs")
                                        .get_child("data");
                for (const auto& second_data : second_datas) {
                    int64_t collection_type_code{0};
                    try {
                        auto collection_type_code_str =
                            second_data.second.get_child("attributes")
                                .get_child("editorialElementKind")
                                .data();
                        collection_type_code = strtoll(
                            collection_type_code_str.c_str(), nullptr, 10);
                    } catch (const std::exception& ex) {
                    }

                    auto third_datas =
                        second_data.second.get_child("relationships")
                            .get_child("children")
                            .get_child("data");
                    for (const auto& third_data : third_datas) {
                        boost::property_tree::ptree forth_datas;
                        try {
                            forth_datas =
                                third_data.second.get_child("relationships")
                                    .get_child("children")
                                    .get_child("data");
                            for (const auto forth_data : forth_datas) {
                                std::string story_label{};
                                int64_t story_id{0};
                                try {
                                    story_id = strtoll(
                                        forth_data.second.get_child("id")
                                            .data()
                                            .c_str(),
                                        nullptr, 10);
                                } catch (const std::exception& ex) {
                                }

                                try {
                                   
                                    story_label =
                                            forth_data.second
                                                .get_child("attributes")
                                                .get_child("designBadge")
                                                .data();
                                   
                                } catch (const std::exception& ex) {
                                }

                                try {
                                    auto fifth_datas =
                                        forth_data.second
                                            .get_child("relationships")
                                            .get_child("contents")
                                            .get_child("data");
                                    for (const auto& fifth_data : fifth_datas) {
                                        int64_t product_key{};
                                        std::string item_type{};
                                        std::string item_note{};
                                        std::string story_note{};

                                        product_key = strtoll(
                                            fifth_data.second.get_child("id")
                                                .data()
                                                .c_str(),
                                            nullptr, 10);

                                        item_type =
                                            fifth_data.second.get_child("type")
                                                .data();
                                        try {
                                            item_note =
                                                fifth_data.second.get_child("attributes")
                                                    .get_child(
                                                        "platformAttributes")
                                                    .get_child("ios")
                                                    .get_child("subtitle")
                                                    .data();
                                        } catch (const std::exception& ex) {
                                        }

                                        try {
                                            story_note =
                                                fifth_data.second.get_child("attributes")
                                                    .get_child(
                                                        "platformAttributes")
                                                    .get_child("ios")
                                                    .get_child("editorialNotes")
                                                    .get_child("tagline")
                                                    .data();
                                        } catch (const std::exception& ex) {
                                        }


                                        Result res {featured_category_key, collection_type_code, story_id, story_label, item_type ,item_note,   story_note,product_key};
                                        results.emplace_back(res);
                                    }
                                   
                                } catch (const std::exception& ex) {
                                }
                            }
                        } catch (const std::exception& ex) {
                        }
                    }
                }
            }
        }

        for (const auto& ele : results) {
            std::cout << ele.product_key << "-->" << ele.featured_category_key
                      << "-->" << ele.collection_type_code << "-->"
                      << ele.story_id << "-->" << ele.story_label << "-->"
                      << ele.item_type << "-->" << ele.item_note << "-->"
                      << ele.story_note << std::endl;

            std::cout << std::endl;
        }

        std::cout << "Total size->" << results.size() << std::endl;

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
