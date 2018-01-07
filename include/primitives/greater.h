
#ifndef LLANGUAGE_GREATER_H
#define LLANGUAGE_GREATER_H

#include "primFun.h"
#include "../value.h"

namespace lr
{
    struct Greater : PrimFun
    {
        ValuePtr apply(const ValuePtrVec& vec, const TokenLocation &lok) override;

        ValueType typeCheck(const ValuePtrVec& vec) override;
    };

}


#endif //LLANGUAGE_GREATER_H
