
#ifndef LLANGUAGE_ENVIRONMENT_H
#define LLANGUAGE_ENVIRONMENT_H

#include <string>
#include <map>
#include "value.h"
#include "token.h"
#include "primitives/primFun.h"

namespace lr
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

        ValuePtr lookup(const std::string &key) const;

        void     putValue(const std::string &key, const ValuePtr &ptr);

        void     putOp(const TokenValue &key, const PrimFunPtr &pfun);

        PrimFunPtr lookupOp(const TokenValue &key);

    protected:
        EnvPtr parent_ = nullptr;
        std::map<std::string, ValuePtr>   varibs_;
        std::map<TokenValue, PrimFunPtr>  prifun_;
    };


}


#endif //LLANGUAGE_ENVIRONMENT_H
