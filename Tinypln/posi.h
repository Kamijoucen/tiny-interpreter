#ifndef PL_POSI_H
#define PL_POSI_H


#include "primFun.h"

namespace cen
{
    struct Posi : public PrimFun
    {

        ValuePtr apply(const ValuePtrVec &vec, const TokenLocation& lok) override;

        ValueType typeCheck(const ValuePtrVec &vec) override;

        ValueType getType() const override;

        std::string toString() const override;

    };
}


#endif //PL_POSI_H
