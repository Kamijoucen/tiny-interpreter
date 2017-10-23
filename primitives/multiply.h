
#ifndef LLANGUAGE_MULTIPLY_H
#define LLANGUAGE_MULTIPLY_H

#include "../value.h"

namespace lr
{
    struct Multiply
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);
    };
}


#endif //LLANGUAGE_MULTIPLY_H
