
#include "util.h"

namespace lr
{
    bool isNumber(const ValuePtr &v)
    {
        ValueType type = v->getType();
        return type == ValueType::INT || type == ValueType::FLOAT;
    }


}

