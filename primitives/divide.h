
#ifndef LLANGUAGE_DIVIDE_H
#define LLANGUAGE_DIVIDE_H

#include "primFun.h"
#include "../include/value.h"

namespace lr
{
    struct Divide : PrimFun
    {
        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation& lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;
    };

}


#endif //LLANGUAGE_DIVIDE_H
