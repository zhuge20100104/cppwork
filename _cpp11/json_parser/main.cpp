#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Result {
    std::string featured_tab_code;
    int64_t story_id;
    std::string story_label;
    std::string story_creative;
    std::string featured_story_title;
    std::string story_note;
    std::string card_display_style;
    int64_t product_key;
};

int main(int argc, char *argv[]) {
    std::vector<Result> results;
    try {
        std::ifstream t("../data.json");
        if (!t) {
            std::cerr << "Can't open file" << std::endl;
            return EXIT_FAILURE;
        }
        std::stringstream ss;
        ss << t.rdbuf();

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);

        BOOST_FOREACH (boost::property_tree::ptree::value_type &v,
                       pt.get_child("results.data")) {
            std::string featured_tab_code{};
            int64_t story_id{};
            std::string story_label{};
            std::string story_creative{};
            std::string featured_story_title{};
            std::string story_note{};
            std::string card_display_style{};
            int64_t product_key{};

            // 第一层过滤date和featured_tab_code
            for (const auto &ele : v.second) {
                std::string title_name = ele.first.data();
                std::string title_value = ele.second.data();

                // 这就是当前 2021-05-01需要的 tree数据
                if (title_name.compare("date") == 0 &&
                    title_value.compare("2021-05-01") == 0) {
                    for (const auto &in_ele : v.second) {
                        if (in_ele.first.compare("title") == 0) {
                            featured_tab_code = in_ele.second.data();
                            // std::cout << featured_tab_code << std::endl;
                        }
                    }
                    BOOST_FOREACH (
                        boost::property_tree::ptree::value_type &contents,
                        v.second.get_child("contents")) {
                        for (const auto &con_ele : contents.second) {
                            std::string in_title_name = con_ele.first.data();
                            if (in_title_name == "id") {
                                story_id = strtoll(
                                    con_ele.second.data().c_str(), nullptr, 10);
                                //   std::cout << story_id << std::endl;
                            }

                            if (in_title_name.compare("attributes") == 0) {
                                story_label =
                                    con_ele.second.get_child("label").data();
                                //   std::cout << story_label << std::endl;
                                try {
                                    story_creative =
                                        con_ele.second
                                            .get_child("editorialArtwork")
                                            .get_child("mediaCard")
                                            .get_child("url")
                                            .data();
                                } catch (const std::exception &ex) {
                                }

                                try {
                                    featured_story_title =
                                        con_ele.second
                                            .get_child("editorialNotes")
                                            .get_child("name")
                                            .data();
                                } catch (const std::exception &ex) {
                                }
                                try {
                                    story_note =
                                        con_ele.second
                                            .get_child("editorialNotes")
                                            .get_child("short")
                                            .data();
                                } catch (const std::exception &ex) {
                                }

                                try {
                                    card_display_style =
                                        con_ele.second
                                            .get_child("cardDisplayStyle")
                                            .data();
                                } catch (const std::exception &ex) {
                                }

                                //   std::cout << story_creative << std::endl;
                                //   std::cout << featured_story_title <<
                                //   std::endl; std::cout << story_note <<
                                //   std::endl; std::cout << card_display_style
                                //   << std::endl;
                            }

                            if (in_title_name.compare("relationships") == 0) {
                                BOOST_FOREACH (const boost::property_tree::
                                                   ptree::value_type &datas,
                                               con_ele.second.get_child(
                                                   "card-contents.data")) {
                                    for (const auto &data : datas.second) {
                                        std::string title_name =
                                            data.first.data();
                                        if (title_name.compare("id") == 0) {
                                            product_key = strtoll(
                                                data.second.data().c_str(),
                                                nullptr, 10);
                                        }
                                        // std::cout << product_key <<
                                        // std::endl;
                                        Result r{featured_tab_code,
                                                 story_id,
                                                 story_label,
                                                 story_creative,
                                                 featured_story_title,
                                                 story_note,
                                                 card_display_style,
                                                 product_key};

                                        results.emplace_back(std::move(r));
                                        break;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    continue;
                }
            }
        }

        for (const auto &ele : results) {
            std::cout << ele.product_key << "-->" << ele.featured_tab_code
                      << "-->" << ele.story_id << " -->" << ele.story_label
                      << " -->" << ele.featured_story_title << "--> "
                      << ele.card_display_style << "--> " << ele.story_creative
                      << "-->" << ele.story_note << std::endl;

            std::cout << std::endl;
        }

        std::cout << "Total size->" << results.size() << std::endl;

        return EXIT_SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
