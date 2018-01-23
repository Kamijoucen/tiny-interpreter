
#include <iostream>
#include <utility>
#include "../util/util.h"
#include "../util/error.h"
#include "../include/ast.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace cen
{

    ValuePtr VariableAST::eval(EnvPtr ptr) {
        return nullptr;
    }

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
            errorInterp("没有发现操作符:");
            return nullptr;
        }

        return fun->apply(vec, getTokenLocation());
    }

    ValuePtr BlockAST::eval(EnvPtr env)
    {
        EnvPtr lenv = makeNewEnv(env);
        for (auto &stat : vec_)
        {
            if (typeid(BreakAST) == typeid(*stat))
            {
                env->changeValue("isNeedBreak", std::make_shared<BoolValue>(true));
                break;
            }
            if (typeid(ContinueAST) == typeid(*stat)) {
                break;
            }
            stat->eval(lenv);
        }
        return VoidValue::instance();
    }

    BlockAST::BlockAST(TokenLocation &lok) : ExprAST(lok) {}

    VariableDefinitionStatementAST::VariableDefinitionStatementAST(VariableASTPtr lhs, ExprASTPtr rhs, TokenLocation location)
            : ExprAST(std::move(location)),
              lhs_(std::move(lhs)),
              rhs_(std::move(rhs)) {}


    ValuePtr VariableDefinitionStatementAST::eval(EnvPtr env)
    {
        if (env->lookupLocation(lhs_->getVarName()))
        {
            errorInterp("变量 " + lhs_->getVarName() + " 定义重复:" + tokenLocation_.toString());
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
            errorInterp("未找到 if 的条件语句");
            return nullptr;
        }

        if (condiv->getType() != ValueType::BOOL)
        {
            errorInterp("if 的条件语句需要一个布尔值");
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
            errorInterp("作用域内没有发现变量: " + name);
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

    VariableUseStatementAST::VariableUseStatementAST(const std::string &varname, TokenLocation lok) : ExprAST(std::move(lok)),
                                                                                                      varname_(varname) {}

    ValuePtr VariableUseStatementAST::eval(EnvPtr ptr)
    {
        auto var = ptr->lookup(varname_);
        if (!var)
        {
            errorInterp("作用域内没有发现变量: " + varname_ + "\t" + tokenLocation_.toString());
            return nullptr;
        }
        return var;
    }

    ValuePtr PrintStatementAST::eval(EnvPtr env)
    {
        std::cout << val_->eval(env)->toString() << std::endl;
        return VoidValue::instance();
    }

    PrintStatementAST::PrintStatementAST(ExprASTPtr val) : val_(std::move(val)) {}


    WhileStatementAST::WhileStatementAST(ExprASTPtr condion, BlockASTPtr body, TokenLocation lok)
            : ExprAST(std::move(lok)),
              condition_(std::move(condion)),
              body_(std::move(body)) {}


    ValuePtr WhileStatementAST::eval(EnvPtr env)
    {
        EnvPtr whileEnv = makeNewEnv(env);

        ValuePtr val = condition_->eval(whileEnv);
        if (val->getType() != ValueType::BOOL)
        {
            errorInterp("while 的条件语句需要一个布尔值:");
            return nullptr;
        }

        whileEnv->putLocationValue("isNeedBreak", std::make_shared<BoolValue>(false));

        while (static_cast<BoolValue*>(val.get())->value_ && !Parser::getErrorFlag())
        {
            body_->eval(whileEnv);
            val = condition_->eval(whileEnv);

            if (static_cast<BoolValue*>(whileEnv->lookup("isNeedBreak").get())->value_)
                break;
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

    BreakAST::BreakAST(const TokenLocation &lok) : ExprAST(lok) {}

    ValuePtr BreakAST::eval(EnvPtr env)
    {
        return cen::ValuePtr();
    }

    ValuePtr ContinueAST::eval(EnvPtr env) {

        return cen::ValuePtr();
    }

    ContinueAST::ContinueAST(const TokenLocation &lok) : ExprAST(lok) {}

    ReturnAST::ReturnAST(const TokenLocation &lok) : ExprAST(lok) {}

    ValuePtr ReturnAST::eval(EnvPtr env) {
        return cen::ValuePtr();
    }

    FunAST::FunAST(const TokenLocation &lok) : ExprAST(lok) {}

    FunAST::FunAST(std::vector<std::string> param, BlockASTPtr body, EnvPtr env, const TokenLocation &lok) : ExprAST(lok),
                                                                                                             param_(std::move(param)),
                                                                                                             body_(std::move(body)),
                                                                                                             funEnv_(std::move(env)) {}

    ValuePtr FunAST::eval(EnvPtr env) {
        return cen::ValuePtr();
    }
}
