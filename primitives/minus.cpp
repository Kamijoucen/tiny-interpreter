
#include "minus.h"

namespace lr
{

    Minus::Minus(const ValuePtr &v1, const ValuePtr &v2) : v1_(v1), v2_(v2) {}

    ValuePtr Minus::apply() {

        return lr::ValuePtr();
    }

    ValueType Minus::typeCheck() {
        return ValueType::FLOAT;
    }


}