#ifndef _FREDRIC_CLASSIC_VISITOR_HPP_
#define _FREDRIC_CLASSIC_VISITOR_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor {
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
    virtual void visit(SubstractionExpression* se) = 0;
};

// 打印表达式内容的Visitor
struct ExpressionPrinter: ExpressionVisitor {
    std::ostringstream oss;
    std::string str() const {
        return oss.str();
    }

    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubstractionExpression* se) override;
};

// 计算表达式值的visitor
struct ExpressionEvaluator: ExpressionVisitor {
    double result;
    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubstractionExpression* se) override;
};

struct Expression {
    virtual ~Expression() = default;
    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression: Expression {
    double value;
    explicit DoubleExpression(double value_): value{value_} {

    }

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

struct AdditionExpression: Expression {
    std::unique_ptr<Expression> left, right;
    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_): left{std::move(left_)}, right{std::move(right_)} {}

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

struct SubstractionExpression: Expression {
    std::unique_ptr<Expression> left, right;
    SubstractionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_): left{std::move(left_)}, right{std::move(right_)} {}

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

void ExpressionPrinter::visit(DoubleExpression* de) {
    oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression* ae) {
    bool need_braces = dynamic_cast<SubstractionExpression*>(ae->right.get());
    ae->left->accept(this);
    oss << "+";
    if(need_braces) oss << "(";
    ae->right->accept(this);
    if(need_braces) oss << ")";
}


void ExpressionPrinter::visit(SubstractionExpression* se) {
    bool need_braces = dynamic_cast<SubstractionExpression*>(se->right.get());
    se->left->accept(this);
    oss << "-";
    if(need_braces) oss << "(";
    se->right->accept(this);
    if(need_braces) oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression* de) {
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression* ae) {
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;
}

void ExpressionEvaluator::visit(SubstractionExpression* se) {
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result = temp - result;
}

#endif