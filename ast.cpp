//
// Created by X6TI on 2017/10/7.
//

#include "ast.h"

lr::ExprAST::ExprAST(lr::TokenLocation loc) : tokenLocation_(std::move(loc)) {}

