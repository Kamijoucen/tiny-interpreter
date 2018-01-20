
#ifndef LLANGUAGE_LESS_H
#define LLANGUAGE_LESS_H

#include "primFun.h"
#include "../value.h"

namespace cen
{
    struct Less : public PrimFun
    {
        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation &lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;

        ValueType getType() const override;

        std::string toString() const override;
    };
}

#endif //LLANGUAGE_LESS_H
