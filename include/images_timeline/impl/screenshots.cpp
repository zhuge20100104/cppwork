#include "images_timeline/screenshots.h"

std::ostream& print_screenshot_value(
    std::ostream& os, const screenshots_value_type& screenshots_value) {
    for (auto&& map_ele : screenshots_value) {
        os << map_ele.first << std::endl;
        auto urls = map_ele.second;
        for (auto&& url : urls) {
            os << url << std::endl;
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const screenshots& screenshot_) {
    os << "Screenshot info: product_key: " << screenshot_.product_key
       << std::endl << " Old value: ";

    print_screenshot_value(os, screenshot_.old_value);

    os << " New value: ";
    print_screenshot_value(os, screenshot_.new_value);

    os << " Meta: ";

    for (auto&& map_ele : screenshot_.meta) {
        os << map_ele.first << " " << map_ele.second << " ";
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const icon_url& icon_url_) {
    os << "product_key: " << icon_url_.product_key << std::endl <<
        " old_url: " << icon_url_.old_url << std::endl <<
        " new_url: " << icon_url_.new_url << std::endl <<
        " change_time: " << icon_url_.change_time;
    return os;
}