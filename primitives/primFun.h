
#ifndef LLANGUAGE_PRIMFUN_H
#define LLANGUAGE_PRIMFUN_H

#include <vector>
#include "../include/value.h"
#include "../include/token.h"

namespace lr
{
    class PrimFun;

    using PrimFunPtr  = std::shared_ptr<PrimFun>;
    using ValuePtrVec = std::vector<ValuePtr>;

    struct PrimFun
    {
        virtual ValuePtr  apply(const ValuePtrVec &vec, const TokenLocation& lok) = 0;

        virtual ValueType typeCheck(const ValuePtrVec &vec) = 0;
    };
}


#endif //LLANGUAGE_PRIMFUN_H
