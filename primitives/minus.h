#ifndef LLANGUAGE_MINUS_H
#define LLANGUAGE_MINUS_H

#include "../value.h"

namespace lr
{
    struct Minus
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);
    };
}

#endif //LLANGUAGE_MINUS_H
