
#ifndef LLANGUAGE_LESS_H
#define LLANGUAGE_LESS_H

#include "../value.h"

namespace lr
{
    struct Less
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);
    };
}

#endif //LLANGUAGE_LESS_H
