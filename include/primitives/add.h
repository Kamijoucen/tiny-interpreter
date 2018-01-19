
#ifndef LLANGUAGE_ADD_H
#define LLANGUAGE_ADD_H

#include "primFun.h"
#include "../environment.h"

namespace lr
{
    struct Add : public PrimFun
    {

        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation& lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;

        ValueType getType() const override;

        std::string toString() const override;

    };
}

#endif //LLANGUAGE_ADD_H
