#ifndef _FREDRIC_STATIC_STRATEGY_HPP_
#define _FREDRIC_STATIC_STRATEGY_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <concepts>

enum class OutputFormat {
    Markdown,
    Html
};

template <typename T>
concept ListStrategyType = requires (T value) {
    {value.add_list_item(std::declval<std::ostringstream&>(), std::declval<std::string const&>())};
    {value.start(std::declval<std::ostringstream&>())};
    {value.end(std::declval<std::ostringstream&>())};
};


struct MarkdownListStrategy {
    void start(std::ostringstream& oss) {
    }
    
    void end(std::ostringstream& oss) {
    }

    void add_list_item(std::ostringstream& oss, std::string const& item) {
        oss << " * " << item << std::endl;
    }
}; 

struct HtmlListStrategy {
    void start(std::ostringstream& oss) {
        oss << "<ul>" << std::endl;
    }

    void end(std::ostringstream& oss) {
        oss << "</ul>" << std::endl;
    }

    void add_list_item(std::ostringstream& oss, std::string const& item) {
        oss << "<li>" << item << "</li>" << std::endl;
    }
};

template <ListStrategyType LS>
struct TextProcessor {
    void clear() {
        oss.str("");
        oss.clear();
    }

    void append_list(std::vector<std::string> const& items) {
        list_strategy.start(oss);
        for(auto& item: items) {
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }


    std::string str() const {
        return oss.str();
    }
private:
    std::ostringstream oss;
    LS list_strategy;
};


#endif