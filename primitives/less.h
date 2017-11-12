
#ifndef LLANGUAGE_LESS_H
#define LLANGUAGE_LESS_H

#include "primFun.h"
#include "../value.h"

namespace lr
{
    struct Less : PrimFun
    {
        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation &lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;
    };
}

#endif //LLANGUAGE_LESS_H
