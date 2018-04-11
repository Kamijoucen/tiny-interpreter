﻿
#ifndef LLANGUAGE_PRIMFUN_H
#define LLANGUAGE_PRIMFUN_H

#include <vector>
#include "value.h"

#define Int     cen::ValueType::INT
#define Float   cen::ValueType::FLOAT

namespace cen
{
    class PrimFun;
    class TokenLocation;

    using PrimFunPtr  = std::shared_ptr<PrimFun>;
    using ValuePtrVec = std::vector<ValuePtr>;

    struct PrimFun : public Value
    {
        virtual ValuePtr  apply(const ValuePtrVec &vec, const TokenLocation& lok) = 0;

        virtual ValueType typeCheck(const ValuePtrVec &vec) = 0;
    };
}


#endif //LLANGUAGE_PRIMFUN_H
