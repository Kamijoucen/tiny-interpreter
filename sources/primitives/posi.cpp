#include "../../include/primitives/posi.h"

namespace cen
{

    ValuePtr Posi::apply(const ValuePtrVec &vec, const TokenLocation &lok)
    {

        return cen::ValuePtr();
    }

    ValueType Posi::typeCheck(const ValuePtrVec &vec) {
        return ValueType::UNKNOWN;
    }

    ValueType Posi::getType() const {
        return ValueType::OP;
    }

    std::string Posi::toString() const {
        return "+";
    }


}
