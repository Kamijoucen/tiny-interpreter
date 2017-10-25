
#include <iostream>
#include <utility>
#include "ast.h"
#include "primitives/add.h"
#include "primitives/minus.h"
#include "primitives/multiply.h"
#include "primitives/divide.h"
#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{

    ValuePtr VariableAST::eval() { return nullptr; }

    VariableAST::VariableAST(std::string str) : varName_(std::move(str)) {}


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

    BinaryExprAST::BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, const TokenLocation &location)
            : ExprAST(location),
              left_(std::move(left)),
              right_(std::move(right)),
              op_(tokenValue) {}


    ValuePtr BinaryExprAST::eval()
    {
        switch (op_)
        {
            case TokenValue::MINUS:     return Minus::   apply(left_->eval(), right_->eval());
            case TokenValue::ADD:       return Add::     apply(left_->eval(), right_->eval());
            case TokenValue::MULTIPLY:  return Multiply::apply(left_->eval(), right_->eval());
            case TokenValue::DIVIDE:    return Divide::  apply(left_->eval(), right_->eval());
            default:                    return nullptr;
        }
    }

    ValuePtr BlockAST::eval() {
        return ExprAST::eval();
    }

    BlockAST::BlockAST(TokenLocation &lok) : ExprAST(lok) {}

    AssignStatementAST::AssignStatementAST(ExprASTPtr lhs, ExprASTPtr rhs, const TokenLocation &location)
            : ExprAST(location),
              lhs_(std::move(lhs)),
              rhs_(std::move(rhs)) {}


    ValuePtr AssignStatementAST::eval()
    {
        return ExprAST::eval();
    }
}
