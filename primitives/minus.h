#ifndef LLANGUAGE_MINUS_H
#define LLANGUAGE_MINUS_H

#include "primFun.h"
#include "../include/value.h"

namespace lr
{
    struct Minus : PrimFun
    {
        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation &lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;
    };
}

#endif //LLANGUAGE_MINUS_H
