
#ifndef LLANGUAGE_GREATER_H
#define LLANGUAGE_GREATER_H

#include "../value.h"

namespace lr
{
    struct Greater
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);

    };

}


#endif //LLANGUAGE_GREATER_H
