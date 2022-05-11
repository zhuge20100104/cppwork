#ifndef _FREDRIC_INTEPRETER_PARSING_HPP_
#define _FREDRIC_INTEPRETER_PARSING_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Token {
    enum Type { integer, plus, minus, lparen, rparen } type;

    std::string text;

    Token(Type type_, std::string const& text_) : type{type_}, text{text_} {}
    friend std::ostream& operator<<(std::ostream& os, Token const& token) {
        os << "`" << token.text << "`";
        return os;
    }
};

std::vector<Token> lex(std::string const& input) {
    std::vector<Token> result;

    for (int i = 0; i < input.size(); ++i) {
        switch (input[i]) {
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
                for (int j = i + 1; j < input.size(); ++j) {
                    if (std::isdigit(input[j])) {
                        buffer << input[j];
                        ++i;
                    } else {
                        result.push_back(Token{Token::integer, buffer.str()});
                        break;
                    }
                }
                break;
        }
    }
    return result;
}

struct Element {
    virtual int eval() const = 0;
};

struct Integer : Element {
    int value;
    Integer(int value_) : value{value_} {}

    int eval() const override { return value; }
};

struct BinaryOperation : Element {
    enum Type { addition, substraction } type;
    std::shared_ptr<Element> lhs, rhs;

    int eval() const override {
        auto left = lhs->eval();
        auto right = rhs->eval();
        if (type == addition) {
            return left + right;
        } else {
            return left - right;
        }
    }
};

std::shared_ptr<Element> parse(std::vector<Token> const& tokens) {
    auto result = std::make_shared<BinaryOperation>();
    bool have_lhs{false};

    for (auto i = 0; i < tokens.size(); ++i) {
        auto& token = tokens[i];
        switch (token.type) {
            case Token::integer: {
                int value = std::atoi(token.text.c_str());
                auto int_ = std::make_shared<Integer>(value);
                if (!have_lhs) {
                    result->lhs = int_;
                    have_lhs = true;
                } else {
                    result->rhs = int_;
                }
            } 
            break;
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            case Token::minus:
                result->type = BinaryOperation::substraction;
                break;
            case Token::lparen: {
                int j = i;
                // 一直找到右括号，就break
                for (; j < tokens.size(); ++j) {
                    if (tokens[j].type == Token::rparen) {
                        break;
                    }
                }

                std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                // 递归解析子表达式
                auto element = parse(subexpression);
                if (!have_lhs) {
                    result->lhs = element;
                    have_lhs = true;
                } else {
                    result->rhs = element;
                }
                // 往前跳到j
                i = j;
            }
            break;
        }
    }
    return result;
}

#endif