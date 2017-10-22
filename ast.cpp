//
// Created by X6TI on 2017/10/7.
//

#include <iostream>
#include "ast.h"
#include "test/test.h"

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
        std::cout << op_;

        switch (op_)
        {
            case TokenValue::ADD:       return add();
            case TokenValue::MINUS:     return minus();
            case TokenValue::MULTIPLY:  return multiply();
            case TokenValue::DIVIDE:    return divide();
            default:
                std::cout << "ast op error" << std::endl;
                break;
        }
    }

    ValuePtr BinaryExprAST::add()
    {
        ValueType Int   = ValueType::INT;
        ValueType Float = ValueType::FLOAT;

        ValuePtr lv = left_    ->eval();
        ValuePtr rv = right_   ->eval();

        if (lv->getType() == Int && rv->getType() == Int)
        {

            return nullptr;
        }

        if (lv->getType() == Float && rv->getType() == Float)
        {

        }

        if (lv->getType() == Float && rv->getType() == Int)
        {

        }

        if (lv->getType() == Int && rv->getType() == Float)
        {

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
