
#include <iostream>
#include <utility>
#include "ast.h"
#include "util/error.h"
#include "parser.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{

    ValuePtr VariableAST::eval(EnvPtr ptr) { return nullptr; }

    VariableAST::VariableAST(std::string str) : varName_(std::move(str)) {}


    IntegerNumExprAST::IntegerNumExprAST(int num, TokenLocation tokenLocation) : ExprAST(std::move(tokenLocation)),
                                                                                 value_(num) {}

    ValuePtr IntegerNumExprAST::eval(EnvPtr ptr)
    {
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


    ValuePtr BinaryExprAST::eval(EnvPtr env)
    {
        std::vector<ValuePtr> vec = {left_->eval(env), right_->eval(env)};
        auto fun = env->lookupOp(op_);
        if (!fun)
        {
            errorSyntax("没有发现操作符 todo");
            return nullptr;
        }

        return fun->apply(vec, getTokenLocation());
    }

    ValuePtr BlockAST::eval(EnvPtr env)
    {
        EnvPtr lenv = std::make_shared<Environment>(env);
        for (auto &stat : vec_)
        {
            stat->eval(lenv);
        }
        return VoidValue::instance();
    }

    BlockAST::BlockAST(TokenLocation &lok) : ExprAST(lok) {}

    VariableDefinitionStatementAST::VariableDefinitionStatementAST(VariableASTPtr lhs, ExprASTPtr rhs,
                                                                   const TokenLocation &location)
            : ExprAST(location),
              lhs_(std::move(lhs)),
              rhs_(std::move(rhs)) {}


    ValuePtr VariableDefinitionStatementAST::eval(EnvPtr env)
    {
        if (env->lookupLocation(lhs_->getVarName()))
        {
            errorSyntax("variable redefinition:" + lhs_->getTokenLocation().toString());
            return nullptr;
        }
        env->putLocationValue(lhs_->getVarName(), rhs_->eval(env));
        return VoidValue::instance();
    }

    IfStatementAST::IfStatementAST(ExprASTPtr condition, ExprASTPtr thenPart, ExprASTPtr elsePart, const TokenLocation &lok)
            : ExprAST(lok),
              condition_(std::move(condition)),
              thenPart_(std::move(thenPart)),
              elsePart_(std::move(elsePart)) {}

    ValuePtr IfStatementAST::eval(EnvPtr env)
    {
        ValuePtr condiv = condition_->eval(env);

        if (!condiv)
        {
            errorSyntax("if condition is null");
            return nullptr;
        }

        if (condiv->getType() != ValueType::BOOL)
        {
            errorSyntax("if condition need bool val");
            return nullptr;
        }

        if (static_cast<BoolValue *>(condiv.get())->value_)
        {
            return thenPart_->eval(env);
        }
        else
        {
            return elsePart_->eval(env);
        }
    }

    ValuePtr VariableAssignStatementAST::eval(EnvPtr env)
    {
        auto name = lhs_->getVarName();
        auto val  = env->lookup(name);
        if (!val)
        {
            errorSyntax("No definitions or declarations of variables found in the scope: " + name);
        }
        else
        {
            env->changeValue(name, rhs_->eval(env));
        }
        return VoidValue::instance();
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

    VariableUseStatementAST::VariableUseStatementAST(const std::string &varname) : varname_(varname) {}

    ValuePtr VariableUseStatementAST::eval(EnvPtr ptr)
    {
        auto var = ptr->lookup(varname_);
        if (!var)
        {
            errorSyntax("No definitions or declarations of variables found in the scope: " + varname_);
            return nullptr;
        }
        return var;
    }

    ValuePtr PrintStatementAST::eval(EnvPtr env)
    {
        using namespace std;
        cout << val_->eval(env)->toString() << endl;
        return VoidValue::instance();
    }

    PrintStatementAST::PrintStatementAST(ExprASTPtr val) : val_(std::move(val)) {}


    WhileStatementAST::WhileStatementAST(ExprASTPtr condion, BlockASTPtr body, const TokenLocation &lok)
            : ExprAST(lok),
              condition_(std::move(condion)),
              body_(std::move(body)) {}


    ValuePtr WhileStatementAST::eval(EnvPtr env)
    {
        ValuePtr val = condition_->eval(env);
        if (val->getType() != ValueType::BOOL)
        {
            errorSyntax("while condition need bool val");
            return nullptr;
        }

        while (static_cast<BoolValue*>(val.get())->value_ && !Parser::getErrorFlag())
        {
            body_->eval(env);
            val = condition_->eval(env);
        }

        return VoidValue::instance();
    }

    StringAST::StringAST(std::string str, const TokenLocation &lok) : ExprAST(lok), value_(std::move(str)) {}

    ValuePtr StringAST::eval(EnvPtr env)
    {
        return std::make_shared<StringValue>(value_);
    }

    UnaryExprAST::UnaryExprAST(ExprASTPtr hs, TokenValue tv, const TokenLocation &lok)
            : ExprAST(lok),
              hs_(std::move(hs)),
              op_(tv) {}

    ValuePtr UnaryExprAST::eval(EnvPtr env)
    {
        // todo
        return nullptr;
    }
}
