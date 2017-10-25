
#ifndef LLANGUAGE_ADD_H
#define LLANGUAGE_ADD_H

#include "../value.h"
#include "../environment.h"

namespace lr
{
    struct Add
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);
    };
}

#endif //LLANGUAGE_ADD_H