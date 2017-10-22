//
// Created by X6TI on 2017/10/7.
//

#include <iostream>
#include "ast.h"
#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{

    IntegerNumExprAST::IntegerNumExprAST(int num, TokenLocation tokenLocation) : ExprAST(std::move(tokenLocation)),
                                                                                 value_(num) {}

    ValuePtr IntegerNumExprAST::eval() {
        return std::make_shared<IntValue>(value_);
    }

    ValuePtr FloatNumExprAST::eval() {
        return std::make_shared<FloatValue>(value_);
    }

    FloatNumExprAST::FloatNumExprAST(float num, TokenLocation tokenLocation) :
            ExprAST(std::move(tokenLocation)),
            value_(num) {}

    ExprAST::ExprAST(TokenLocation loc) : tokenLocation_(std::move(loc)) {}

    BinaryExprAST::BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &location)
            : ExprAST(location),
              left_(std::move(left)),
              right_(std::move(right)),
              op_(tokenValue) {}

    BinaryExprAST::BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &&location)
            : BinaryExprAST(std::move(left), std::move(right), tokenValue, location) {}

    ValuePtr BinaryExprAST::eval()
    {
        switch (op_)
        {
            case TokenValue::ADD:       return add();
            case TokenValue::MINUS:     return minus();
            case TokenValue::MULTIPLY:  return multiply();
            case TokenValue::DIVIDE:    return divide();
            default:                    return nullptr;
        }
    }

    ValuePtr BinaryExprAST::add()
    {
        ValuePtr lv = left_    ->eval();
        ValuePtr rv = right_   ->eval();
        if (lv->getType() == Int && rv->getType() == Int)
        {
            auto l = static_cast<IntValue*>(lv.get());
            auto r = static_cast<IntValue*>(rv.get());
            return std::make_shared<IntValue>(l->value_ + r->value_);
        }

        if (lv->getType() == Float && rv->getType() == Float)
        {
            auto l = static_cast<FloatValue*>(lv.get());
            auto r = static_cast<FloatValue*>(rv.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (lv->getType() == Float && rv->getType() == Int)
        {
            auto l = static_cast<FloatValue*>(lv.get());
            auto r = static_cast<IntValue*>(rv.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (lv->getType() == Int && rv->getType() == Float)
        {
            auto l = static_cast<IntValue*>(lv.get());
            auto r = static_cast<FloatValue*>(rv.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }
        return nullptr;
    }

    ValuePtr BinaryExprAST::minus() {
        return lr::ValuePtr();
    }

    ValuePtr BinaryExprAST::multiply() {
        return lr::ValuePtr();
    }

    ValuePtr BinaryExprAST::divide() {
        return lr::ValuePtr();
    }

}
