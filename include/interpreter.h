
#ifndef LLANGUAGE_INTERPRETER_H
#define LLANGUAGE_INTERPRETER_H

#include <string>
#include <vector>
#include "environment.h"


namespace cen
{

    class Interpreter
    {
    public:
        Interpreter() = default;

        void interp(const std::string &file);

        inline bool getErrorFlag();

        static void setErrorFlag(bool);

    private:
        static bool errorFlag;
    };
    inline bool Interpreter::getErrorFlag() { return errorFlag; }

}

#endif //LLANGUAGE_INTERPRETER_H
