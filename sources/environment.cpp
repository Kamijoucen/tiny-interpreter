
#include "../include/environment.h"

#include "../include/primitives/add.h"
#include "../include/primitives/divide.h"
#include "../include/primitives/greater.h"
#include "../include/primitives/less.h"
#include "../include/primitives/multiply.h"
#include "../include/primitives/minus.h"
#include "../include/primitives/equal.h"
#include "../include/primitives/posi.h"

namespace cen
{
    EnvPtr Environment::baseEnv_ = baseInstance();

    Environment::Environment(EnvPtr penv) : parent_(std::move(penv)) {}

    inline EnvPtr Environment::baseInstance()
    {
        EnvPtr env = std::make_shared<Environment>();
        env->putLocationOp(TokenValue::ADD,          std::make_unique<Add>());
        env->putLocationOp(TokenValue::MINUS,        std::make_unique<Minus>());
        env->putLocationOp(TokenValue::MULTIPLY,     std::make_unique<Multiply>());
        env->putLocationOp(TokenValue::DIVIDE,       std::make_unique<Divide>());
        env->putLocationOp(TokenValue::GREATER_THAN, std::make_unique<Greater>());
        env->putLocationOp(TokenValue::LESS_THAN,    std::make_unique<Less>());
        env->putLocationOp(TokenValue::EQUAL,        std::make_unique<Equal>());
        env->putLocationOp(TokenValue::POSI,         std::make_unique<Posi>());
        return env;
    }

    EnvPtr Environment::buildInitScope()
    {
        return std::make_shared<Environment>(baseEnv_);
    }

    ValuePtr Environment::lookup(const std::string &key) const
    {
        auto iter = varibs_.find(key);
        if (iter == varibs_.end())
        {
            if (parent_)
            {
                return parent_->lookup(key);
            }
            return nullptr;
        }
        return iter->second;
    }

    PrimFunPtr Environment::lookupOp(const TokenValue &key) const
    {
        auto iter = prifun_.find(key);
        if (iter == prifun_.end())
        {
            if (parent_)
            {
                return parent_->lookupOp(key);
            }
            return nullptr;
        }
        return iter->second;
    }

    void Environment::putLocationValue(const std::string &key, const ValuePtr &ptr)
    {
        varibs_.insert({key, ptr});
    }

    void Environment::putLocationOp(const TokenValue &key, const PrimFunPtr &pfun)
    {
        prifun_.insert({key, pfun});
    }

    bool Environment::changeOp(const TokenValue &key, const PrimFunPtr &pfun)
    {
        auto iter = prifun_.find(key);
        if (iter == prifun_.end())
        {
            if (parent_)
            {
                return parent_->changeOp(key, pfun);
            }
            return false;
        }
        else
        {
            prifun_[key] = pfun;
            return true;
        }
    }

    bool Environment::changeValue(const std::string &key, const ValuePtr &ptr)
    {
        auto iter = varibs_.find(key);
        if (iter == varibs_.end())
        {
            if (parent_)
            {
                return parent_->changeValue(key, ptr);
            }
            return false;
        }
        else
        {
            varibs_[key] = ptr;
            return true;
        }
    }

    ValuePtr Environment::lookupLocation(const std::string &key) const
    {
        auto iter = varibs_.find(key);
        if (iter == varibs_.end())
        {
            return nullptr;
        }
        return iter->second;
    }

    PrimFunPtr Environment::lookupOpLocation(const TokenValue &key) const
    {
        auto iter = prifun_.find(key);
        if (iter == prifun_.end())
        {
            return nullptr;
        }
        return iter->second;
    }

}