
#ifndef LLANGUAGE_MULTIPLY_H
#define LLANGUAGE_MULTIPLY_H

#include "primFun.h"
#include "../value.h"

namespace lr
{
    struct Multiply : PrimFun
    {
        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation &lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;
    };
}


#endif //LLANGUAGE_MULTIPLY_H
