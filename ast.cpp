
#include <iostream>
#include "ast.h"
#include "primitives/add.h"
#include "primitives/minus.h"
#include "primitives/multiply.h"
#include "primitives/divide.h"
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
            case TokenValue::MINUS:     return Minus::apply(left_->eval(), right_->eval());
            case TokenValue::ADD:       return Add::apply(left_->eval(), right_->eval());
            case TokenValue::MULTIPLY:  return Multiply::apply(left_->eval(), right_->eval());
            case TokenValue::DIVIDE:    return Divide::apply(left_->eval(), right_->eval());
            default:                    return nullptr;
        }
    }

}
