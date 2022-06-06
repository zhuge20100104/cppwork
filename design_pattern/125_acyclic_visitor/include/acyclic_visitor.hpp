#ifndef _FREDRIC_ACYCLIC_VISITOR_HPP_
#define _FREDRIC_ACYCLIC_VISITOR_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

template <typename Visitable>
struct Visitor {
    virtual void visit(Visitable& obj) = 0;
};

// 标记接口
struct VisitorBase {
    virtual ~VisitorBase() = default;
};



struct Expression {
    virtual ~Expression() = default;
    virtual void accept(VisitorBase& visitor) {
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&visitor)) {
            ev->visit(*this);
        }
    }
};


struct DoubleExpression: Expression {
    double value;
    explicit DoubleExpression(double value_): value{value_} {

    }

    void accept(VisitorBase& visitor) override {
        using DEV = Visitor<DoubleExpression>;
        if(auto ev = dynamic_cast<DEV*>(&visitor)) {
            ev->visit(*this);
        }
    }
};


struct AdditionExpression: Expression {
    std::unique_ptr<Expression> left, right;
    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_): left{std::move(left_)}, right{std::move(right_)} {}

    void accept(VisitorBase& visitor) override {
        using AEV = Visitor<AdditionExpression>;
        if(auto ev = dynamic_cast<AEV*>(&visitor)) {
            ev->visit(*this);
        }
    }
};

struct SubstractionExpression: Expression {
    std::unique_ptr<Expression> left, right;
    SubstractionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_): left{std::move(left_)}, right{std::move(right_)} {}

    void accept(VisitorBase& visitor) override {
        using SEV = Visitor<SubstractionExpression>;
        if(auto ev = dynamic_cast<SEV*>(&visitor)) {
            ev->visit(*this);
        }
    }
};

struct ExpressionPrinter: VisitorBase, 
                        Visitor<Expression>,
                        Visitor<DoubleExpression>,
                        Visitor<AdditionExpression>,
                        Visitor<SubstractionExpression> {

    void visit(Expression& obj) override{

    }

    void visit(DoubleExpression& obj) override {
        oss << obj.value;
    }

    void visit(AdditionExpression& obj) override {
        bool need_braces = dynamic_cast<SubstractionExpression*>(obj.right.get());
        obj.left->accept(*this);
        oss << "+";
        if(need_braces) oss << "(";
        obj.right->accept(*this);
        if(need_braces) oss << ")";
    }

    void visit(SubstractionExpression& obj) override {
        bool need_braces = dynamic_cast<SubstractionExpression*>(obj.right.get());
        obj.left->accept(*this);
        oss << "-";
        if(need_braces) oss << "(";
        obj.right->accept(*this);
        if(need_braces) oss << ")";
    }

    std::string str() const {
        return oss.str();
    }

private:
    std::ostringstream oss;
};

struct ExpressionEvaluator: VisitorBase, 
                        Visitor<Expression>,
                        Visitor<DoubleExpression>,
                        Visitor<AdditionExpression>,
                        Visitor<SubstractionExpression> {

    void visit(Expression& obj) override{

    }

    void visit(DoubleExpression& obj) override {
        result = obj.value;
    }

    void visit(AdditionExpression& obj) override {
        obj.left->accept(*this);
        auto temp = result;
        obj.right->accept(*this);
        result += temp;
    }

    void visit(SubstractionExpression& obj) override {
        obj.left->accept(*this);
        auto temp = result;
        obj.right->accept(*this);
        result = temp - result;
    }

    double result;
};

#endif