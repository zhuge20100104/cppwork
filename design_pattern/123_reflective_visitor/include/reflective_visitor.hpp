#ifndef _FREDRIC_INTRUSIVE_VISITOR_HPP_
#define _FREDRIC_INTRUSIVE_VISITOR_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <typeinfo>

struct Expression {
    virtual ~Expression() = default;
};

struct DoubleExpression: Expression {
    double value;
    explicit DoubleExpression(double value_): value{value_} {

    }
};

struct AdditionExpression: Expression {
    std::unique_ptr<Expression> left, right;
    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_): left{std::move(left_)}, right{std::move(right_)} {}
};

struct ExpressionPrinter {
    std::ostringstream oss;
    
    void print(Expression* e) {
        // 这种做法不好，if-else太多，而且有性能损失dynamic_cast
        // 如果忘记某个条件，还会丢失数据
        if(typeid(*e) == typeid(DoubleExpression)) {
            auto de = dynamic_cast<DoubleExpression*>(e);
            oss << de->value;
        } else if(typeid(*e) == typeid(AdditionExpression)) {
            auto ae = dynamic_cast<AdditionExpression*>(e);
            oss << "(";
            print(ae->left.get());
            oss << "+";
            print(ae->right.get());
            oss << ")";
        }
    }

    std::string str() const {
        return oss.str();
    }
};
#endif