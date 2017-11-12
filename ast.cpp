
#include <iostream>
#include <utility>
#include "ast.h"
#include "util/error.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{

    ValuePtr VariableAST::eval(EnvPtr ptr) { return nullptr; }

    VariableAST::VariableAST(std::string str) : varName_(std::move(str)) {}


    IntegerNumExprAST::IntegerNumExprAST(int num, TokenLocation tokenLocation) : ExprAST(std::move(tokenLocation)),
                                                                                 value_(num) {}

    ValuePtr IntegerNumExprAST::eval(EnvPtr ptr) {
        return std::make_shared<IntValue>(value_);
    }

    ValuePtr FloatNumExprAST::eval(EnvPtr ptr) {
        return std::make_shared<FloatValue>(value_);
    }

    FloatNumExprAST::FloatNumExprAST(float num, TokenLocation tokenLocation) :
            ExprAST(std::move(tokenLocation)),
            value_(num) {}

    ExprAST::ExprAST(TokenLocation loc) : tokenLocation_(std::move(loc)) {}

    BinaryExprAST::BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue,
                                 const TokenLocation &location)
            : ExprAST(location),
              left_(std::move(left)),
              right_(std::move(right)),
              op_(tokenValue) {}


    ValuePtr BinaryExprAST::eval(EnvPtr ptr)
    {
        std::vector<ValuePtr> vec = {left_->eval(ptr), right_->eval(ptr)};
        auto fun = ptr->lookupOp(op_);
        if (!fun)
        {
            errorSyntax("没有发现操作符 todo");
            return nullptr;
        }

        return fun->apply(vec, getTokenLocation());
    }

    ValuePtr BlockAST::eval(EnvPtr ptr)
    {
    }

    BlockAST::BlockAST(TokenLocation &lok) : ExprAST(lok) {}

    VariableDefinitionStatementAST::VariableDefinitionStatementAST(VariableASTPtr lhs, ExprASTPtr rhs,
                                                                   const TokenLocation &location)
            : ExprAST(location),
              lhs_(std::move(lhs)),
              rhs_(std::move(rhs)) {}


    ValuePtr VariableDefinitionStatementAST::eval(EnvPtr ptr)
    {
        std::string vname = lhs_->getVarName();


        return nullptr;
    }

    IfStatementAST::IfStatementAST(ExprASTPtr condition, ExprASTPtr thenPart) : condition_(std::move(condition_)),
                                                                                thenPart_(std::move(thenPart)),
                                                                                elsePart_(nullptr) {}

    ValuePtr VariableAssignStatementAST::eval(EnvPtr ptr)
    {

    }

    VariableAssignStatementAST::VariableAssignStatementAST(VariableASTPtr lhs, ExprASTPtr rhs,
                                                           const TokenLocation &location) : ExprAST(location),
                                                                                            lhs_(std::move(lhs)),
                                                                                            rhs_(std::move(rhs)) {}

    BoolAST::BoolAST(bool val, const TokenLocation &lok) : ExprAST(lok),
                                                           value_(val) {}

    ValuePtr BoolAST::eval(EnvPtr ptr)
    {
        return std::make_unique<BoolValue>(value_);
    }

    VariableUseStatementAST::VariableUseStatementAST(const std::string &varname) : varname_(std::move(varname)) {}

    ValuePtr VariableUseStatementAST::eval(EnvPtr ptr)
    {
        auto var = ptr->lookup(varname_);
        if (!var)
        {
            errorSyntax("No definitions or declarations of variables found in the scope:" + varname_);
            return nullptr;
        }
        return var;
    }
}
