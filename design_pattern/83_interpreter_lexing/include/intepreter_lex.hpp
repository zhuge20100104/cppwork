#ifndef _FREDRIC_INTEPRETER_LEX_HPP_
#define _FREDRIC_INTEPRETER_LEX_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Token {
    enum Type {
        integer,
        plus,
        minus,
        lparen,
        rparen
    } type;

    std::string text;

    Token(Type type_, std::string const& text_): type{type_}, text{text_} {}
    friend std::ostream& operator<<(std::ostream& os, Token const& token) {
        os << "`" << token.text << "`";
        return os;
    }
};

std::vector<Token> lex(std::string const& input) {
    std::vector<Token> result;

    for(int i=0; i<input.size(); ++i) {
        switch(input[i]) {
            case '+':
                result.push_back(Token{Token::plus, "+"});
                break;
            case '-':
                result.push_back(Token{Token::minus, "-"});
                break;
            case '(':
                result.push_back(Token{Token::lparen, "("});
                break;
            case ')':
                result.push_back(Token{Token::rparen, ")"});
                break;
            default:
                // default 解析整型，一直到没有数字为止
                std::ostringstream buffer;
                buffer << input[i];
                for(int j=i+1; j<input.size(); ++j) {
                    if(std::isdigit(input[j])) {
                        buffer << input[j];
                        ++i;
                    }else {
                        result.push_back(Token{Token::integer, buffer.str()});
                        break;
                    }
                }
                break;
        }
    }
    return result;
}

#endif