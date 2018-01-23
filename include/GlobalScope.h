
#ifndef PL_GLOBALSCOPE_H
#define PL_GLOBALSCOPE_H

#include <map>
#include <string>
#include "value.h"

namespace cen
{

    // sb
    struct GlobalScope
    {
        static void put(const std::string &name, ValuePtr val);

        static ValuePtr get(const std::string &name);

        static std::map<std::string, ValuePtr> vars;
    };
}


#endif //PL_GLOBALSCOPE_H
