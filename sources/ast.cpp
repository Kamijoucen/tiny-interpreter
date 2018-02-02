
#include <iostream>
#include <utility>
#include "../util/util.h"
#include "../util/error.h"
#include "../include/ast.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/innerscope.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace cen
{
    EnvPtr makeNewEnv(EnvPtr env) {
        return std::make_shared<Environment>(env);
    }

    ValuePtr VariableAST::eval(EnvPtr env) {
        return nullptr;
    }

    VariableAST::VariableAST(std::string str) : varName_(std::move(str)) {}


    IntegerNumExprAST::IntegerNumExprAST(int num, TokenLocation tokenLocation) : ExprAST(std::move(tokenLocation)),
                                                                                 value_(num) {}

    ValuePtr IntegerNumExprAST::eval(EnvPtr env)
    {
        return std::make_shared<IntValue>(value_);
    }

    ValuePtr FloatNumExprAST::eval(EnvPtr env)
    {
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
        lenv->putLocationValue("isNeedContinue", std::make_shared<BoolValue>(false));
        for (auto &stat : vec_)
        {
            // todo
            if (static_cast<BoolValue*>(lenv->lookup("isNeedContinue").get())->value_) {
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

//    ValuePtr VariableDefinitionStatementAST::eval(EnvPtr env) {
//        return cen::ValuePtr();
//    }


    ValuePtr VariableDefinitionStatementAST::eval(EnvPtr env)
    {
        if (env->lookupLocation(lhs_->getVarName()))
        {
            errorInterp("变量 " + lhs_->getVarName() + " 定义重复:" + tokenLocation_.toString());
            return nullptr;
        }
        auto rval = rhs_->eval(env);
        env->putLocationValue(lhs_->getVarName(), rval);
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

    ValuePtr BoolAST::eval(EnvPtr env)
    {
        return std::make_unique<BoolValue>(value_);
    }

    VariableUseStatementAST::VariableUseStatementAST(const std::string &varname, TokenLocation lok) : ExprAST(std::move(lok)),
                                                                                                      varname_(varname) {}

    ValuePtr VariableUseStatementAST::eval(EnvPtr env)
    {
        auto var = env->lookup(varname_);
        if (!var)
        {
            errorInterp("作用域内没有发现变量: " + varname_ + "\t" + tokenLocation_.toString());
            return nullptr;
        }
        return var;
    }

    ValuePtr PrintStatementAST::eval(EnvPtr env)
    {
        ValuePtr value = val_->eval(env);
        if (!value) {
            errorInterp("print语句没有找到需要打印的值");
            return nullptr;
        }
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
        env->changeValue("isNeedBreak", std::make_shared<BoolValue>(true));
        return NoneValue::instance();
    }

    ValuePtr ContinueAST::eval(EnvPtr env)
    {
        env->changeValue("isNeedContinue", std::make_shared<BoolValue>(true));
        return NoneValue::instance();
    }

    ContinueAST::ContinueAST(const TokenLocation &lok) : ExprAST(lok) {}

    ReturnAST::ReturnAST(const TokenLocation &lok) : ExprAST(lok) {}

    ValuePtr ReturnAST::eval(EnvPtr env) {
        return cen::ValuePtr();
    }

    FunAST::FunAST(std::string name, std::vector<std::string> param, BlockASTPtr body, const TokenLocation &lok)
                                                                                                : ExprAST(lok),
                                                                                                  param_(std::move(param)),
                                                                                                  name_(std::move(name)),
                                                                                                  body_(std::move(body)){}

    ValuePtr FunAST::eval(EnvPtr env) { return body_->eval(env); }

    AnonymousFunAST::AnonymousFunAST(std::vector<std::string> param, std::vector<std::string> envParam, BlockASTPtr body, TokenLocation lok)
                                                                                            : ExprAST(std::move(lok)),
                                                                                              envParam_(std::move(envParam)),
                                                                                              param_(std::move(param)),
                                                                                              body_(std::move(body)),
                                                                                              closureEnv_(nullptr){}

    ValuePtr AnonymousFunAST::eval(EnvPtr env)
    {
        closureEnv_ = std::make_shared<Environment>();
        for (auto &name : envParam_) {
            closureEnv_->putLocationValue(name, env->lookup(name));
        }
        return std::make_shared<Closure>(param_, body_, closureEnv_);
    }

    CallAST::CallAST(std::string name, std::vector<ExprASTPtr> param, TokenLocation lok) : ExprAST(std::move(lok)),
                                                                                            name_(std::move(name)),
                                                                                            param_(std::move(param)){}

    ValuePtr CallAST::eval(EnvPtr env)
    {
        if (ValuePtr funVal = env->lookup(name_))
        {
            if (funVal->getType() == ValueType::CLOSURE)
            {
                auto closure = static_cast<Closure*>(funVal.get());
                auto iter = param_.begin();
                for (auto &name : closure->param_)
                {
                    if (iter != param_.end()) {
                        closure->closureEnv_->putLocationValue(name, (*iter++)->eval(env));
                    } else {
                        closure->closureEnv_->putLocationValue(name, NoneValue::instance());
                    }
                }
                return closure->body_->eval(closure->closureEnv_);
            }
        }


        if (GlobalExprASTPtr gfun = FileScope::getFunction(tokenLocation_.filename_, name_))
        {
            EnvPtr callEvn = makeNewEnv(env);
            const std::vector<std::string> &paramName = gfun->param_;
            auto iter = param_.begin();
            for (auto &name : paramName)
            {
                if (iter != param_.end()) {
                    callEvn->putLocationValue(name, (*iter++)->eval(callEvn));
                } else {
                    callEvn->putLocationValue(name, NoneValue::instance());
                }
            }
            return gfun->eval(callEvn);
        }
        else
        {
            errorInterp("没有找到名为 " + name_ + " 的函数\t" + tokenLocation_.toString());
            return nullptr;
        }
    }

}
