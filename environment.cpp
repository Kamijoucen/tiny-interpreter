
#include "environment.h"

#include <utility>
#include "primitives/add.h"
#include "primitives/divide.h"
#include "primitives/greater.h"
#include "primitives/less.h"
#include "primitives/multiply.h"
#include "primitives/minus.h"

namespace lr
{
    Environment::Environment(EnvPtr penv) : parent_(std::move(penv)) {}

    EnvPtr Environment::buildInitScope()
    {
        EnvPtr env = std::make_unique<Environment>();
        env->putOp(TokenValue::ADD,          std::make_unique<Add>());
        env->putOp(TokenValue::MINUS,        std::make_unique<Minus>());
        env->putOp(TokenValue::MULTIPLY,     std::make_unique<Multiply>());
        env->putOp(TokenValue::DIVIDE,       std::make_unique<Divide>());
        env->putOp(TokenValue::GREATER_THAN, std::make_unique<Greater>());
        env->putOp(TokenValue::LESS_THAN,    std::make_unique<Less>());
        return env;
    }

    ValuePtr Environment::lookup(const std::string &key) const
    {
        auto iter = varibs_.find(key);
        if (iter == varibs_.end())
        {
            return nullptr;
        }
        return iter->second;
    }

    void Environment::putValue(const std::string &key, const ValuePtr &ptr)
    {
        varibs_.insert({key, ptr});
    }

    void Environment::putOp(const TokenValue &key, const PrimFunPtr &pfun)
    {
        prifun_.insert({key, pfun});
    }

    PrimFunPtr Environment::lookupOp(const TokenValue &key)
    {
        auto iter = prifun_.find(key);
        if (iter == prifun_.end())
        {
            return nullptr;
        }
        return iter->second;
    }

}