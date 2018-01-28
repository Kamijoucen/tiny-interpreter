
#ifndef PL_GLOBALSCOPE_H
#define PL_GLOBALSCOPE_H

#include <map>
#include <string>
#include "ast.h"

namespace cen
{
    class FileScope
    {
    public:
        static void putFunction(const std::string &filename, const std::string &key, GlobalExprASTPtr ast);

        static GlobalExprASTPtr getFunction(const std::string &filename, const std::string &key);

        static std::map<std::string, std::map<std::string, GlobalExprASTPtr>> funTable;

    };


}


#endif //PL_GLOBALSCOPE_H
