#ifndef _FREDRIC_GROOVY_BUILDER_HPP_
#define _FREDRIC_GROOVY_BUILDER_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>

namespace html {
    struct Tag {
        std::string name;
        std::string text;

        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;

        friend std::ostream& operator<<(std::ostream& os, Tag const& tag) {
            os << "<" << tag.name;
            for(auto const& att: tag.attributes) {
                os << " " << att.first << "=\"" << att.second << "\"";
            }

            // 没有子tag，没有文本，直接结束
            if(tag.children.size() == 0 && tag.text.length() == 0) {
                os << "/>" << std::endl;
            } else {
                os << ">" << std::endl;

                if(tag.text.length()) {
                    os << tag.text << std::endl;
                }

                for(auto const& child: tag.children) {
                    os << child;
                }
                os << "</" << tag.name << ">" << std::endl;
            }
            return os;
        }

        protected:
            Tag(std::string const& name_, std::string const& text_): name{name_}, text{text_} {}

            Tag(std::string const& name_, std::vector<Tag> const& childs_): name{name_}, children{childs_} {}
    };

    struct P: Tag {
        explicit P(std::string const& text): Tag("p", text) {}

        P(std::initializer_list<Tag> const& children_): Tag("p", children_) {}
    };

    struct IMG: Tag {
        explicit IMG(std::string const& url): Tag("img", "") {
            attributes.emplace_back(std::make_pair("src", url));
        }
    };
};
#endif