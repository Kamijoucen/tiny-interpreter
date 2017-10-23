#ifndef LLANGUAGE_MINUS_H
#define LLANGUAGE_MINUS_H

#include "../value.h"

namespace lr
{
    class Minus
    {
    public:

        Minus(const ValuePtr &v1, const ValuePtr &v2);

        ValuePtr apply();

        ValueType typeCheck();

    private:
        const ValuePtr &v1_, &v2_;
    };
}

#endif //LLANGUAGE_MINUS_H
