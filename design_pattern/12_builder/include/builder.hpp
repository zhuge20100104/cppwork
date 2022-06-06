#ifndef _FREDRIC_BUILDER_HPP_
#define _FREDRIC_BUILDER_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>

struct HTMLElement {
    std::string name;
    std::string text;
    std::size_t const indent_size = 2;
    std::vector<HTMLElement> elements;

    HTMLElement() {}
    HTMLElement(std::string const& name_, std::string const& text_): name{name_}, text{text_} {}

    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0) {
            oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;
        }
        for(auto const& e: elements) {
            oss << e.str(indent + 1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

struct HTMLBuilder {
    HTMLElement root;

    HTMLBuilder(std::string root_name) {
        root.name = root_name;
    }

    void add_child(std::string child_name, std::string child_text) {
        HTMLElement e {child_name, child_text};
        root.elements.emplace_back(e);
    }

    std::string str() const {
        return root.str();
    }
};
#endif