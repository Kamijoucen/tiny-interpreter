//
// Created by X6TI on 2017/10/7.
//

#include "ast.h"

lr::ExprAST::ExprAST(lr::TokenLocation loc) : tokenLocation_(std::move(loc)) {}

lr::BinaryExprAST::BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &location)
        : left_(std::move(left)),
          right_(std::move(right)),
          op_(tokenValue),
          tokenLocation_(location) {}

