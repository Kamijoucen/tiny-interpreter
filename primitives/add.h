
#ifndef LLANGUAGE_ADD_H
#define LLANGUAGE_ADD_H

#include <vector>
#include "../value.h"
#include "../environment.h"

namespace lr
{
    class Add
    {
    public:

        Add(const ValuePtr &v1, const ValuePtr &v2);

        ValuePtr apply();

        ValueType typeCheck();

    private:
        const ValuePtr &v1_, &v2_;
    };
}

#endif //LLANGUAGE_ADD_H
