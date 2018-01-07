
#ifndef LLANGUAGE_ADD_H
#define LLANGUAGE_ADD_H

#include "primFun.h"
#include "../include/environment.h"

namespace lr
{
    struct Add : PrimFun
    {

        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation& lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;
    };
}

#endif //LLANGUAGE_ADD_H
