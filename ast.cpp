//
// Created by X6TI on 2017/10/7.
//

#include "ast.h"

namespace lr
{

    IntegerNumExprAST::IntegerNumExprAST(int num, TokenLocation tokenLocation) : ExprAST(std::move(tokenLocation)),
                                                                                 value_(num) {}

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

}
