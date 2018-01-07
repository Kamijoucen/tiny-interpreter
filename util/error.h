
#ifndef LLANGUAGE_ERROR_H
#define LLANGUAGE_ERROR_H

#include "string"

namespace lr
{
    extern void errorToken(const std::string& msg);
    extern void errorSyntax(const std::string& msg);
    extern void errorInterp(const std::string &msg);
}


#endif //LLANGUAGE_ERROR_H
