
#ifndef PL_GLOBALSCOPE_H
#define PL_GLOBALSCOPE_H

#include <map>
#include <string>
#include "ast.h"

namespace cen
{
    struct FileScope
    {
        static std::map<std::string, std::map<std::string, ExprASTPtr>> funTable;

    };
}


#endif //PL_GLOBALSCOPE_H
