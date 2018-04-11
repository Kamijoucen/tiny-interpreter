﻿
#ifndef LLANGUAGE_ENVIRONMENT_H
#define LLANGUAGE_ENVIRONMENT_H

#include <string>
#include <map>
#include "value.h"
#include "token.h"
#include "primFun.h"

namespace cen
{

    class Environment;

    using EnvPtr = std::shared_ptr<Environment>;

    class Environment
    {
    public:
        Environment() = default;

        explicit Environment(EnvPtr penv);

    public:
        static EnvPtr buildInitScope();

        bool       changeOp(const TokenValue &key, const PrimFunPtr &pfun);

        bool       changeValue(const std::string &key, const ValuePtr &ptr);

        // location

        void       putLocationOp(const TokenValue &key, const PrimFunPtr &pfun);

        void       putLocationValue(const std::string &key, const ValuePtr &ptr);

        ValuePtr   lookup(const std::string &key) const;

        ValuePtr   lookupLocation(const std::string &key) const;

        PrimFunPtr lookupOp(const TokenValue &key) const;

        PrimFunPtr lookupOpLocation(const TokenValue &key) const;

        // inner


    private:
        static inline EnvPtr baseInstance();

    private:
        EnvPtr parent_ = nullptr;
        std::map<std::string, ValuePtr>   varibs_;
        std::map<std::string, ValuePtr>   innerVaribs_;
        std::map<TokenValue, PrimFunPtr>  prifun_;
        static EnvPtr baseEnv_;
    };




}


#endif //LLANGUAGE_ENVIRONMENT_H
