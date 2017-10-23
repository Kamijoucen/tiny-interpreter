
#ifndef LLANGUAGE_DIVIDE_H
#define LLANGUAGE_DIVIDE_H

#include "../value.h"

namespace lr
{
    struct Divide
    {
        static ValuePtr apply(const ValuePtr &v1, const ValuePtr &v2);

        static ValueType typeCheck(const ValuePtr &v1, const ValuePtr &v2);
    };

}


#endif //LLANGUAGE_DIVIDE_H
