#ifndef _FREDRIC_TEXT_FORMATTER_HPP_
#define _FREDRIC_TEXT_FORMATTER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class FormattedText {
    std::string plain_text;
    std::vector<bool> caps;

public:
    FormattedText(std::string const& plain_text_): plain_text{plain_text_}, caps(plain_text_.size(), false){
    }

    ~FormattedText() {
    }

    void capitalize(int start, int end) {
        for(int i=start; i<=end; ++i) {
            caps[i] = true;  
        }
    }

    friend std::ostream& operator<<(std::ostream& os, FormattedText const& obj) {
        std::stringstream ss;
        for(auto i=0; i<obj.plain_text.size(); ++i) {
            char c = obj.plain_text[i];
            ss << static_cast<char>(obj.caps[i] ? std::toupper(c): c);
        }
        return os << ss.str();
    }
};

class BetterFormattedText {
public:
    BetterFormattedText(std::string const& plain_text_): plain_text{plain_text_} {}

    struct TextRange {
        int start, end;
        bool capitalize; // 或者 bold, italic

        bool covers(int position) const {
            return position >=start && position <=end;
        }
    };

    TextRange& get_range(int start, int end) {
        formatting.emplace_back(start, end);
        return *formatting.rbegin();
    }

    friend std::ostream& operator<<(std::ostream& os, BetterFormattedText const& obj){
        std::stringstream ss;
        for(auto i=0; i<obj.plain_text.size(); ++i) {
            auto c = obj.plain_text[i];
            // Apply ranges
            for(auto&& rng: obj.formatting) {
                if(rng.covers(i) && rng.capitalize) {
                    c = std::toupper(c);
                    break;
                }
            }
            ss << static_cast<char>(c);
        }
        return os << ss.str();
    }

private:
    std::string plain_text;
    std::vector<TextRange> formatting;
};


#endif