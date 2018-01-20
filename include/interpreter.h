
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
        Interpreter();

        void interp(const std::string &file);

        void interp(const std::vector<std::string> &files);

        inline bool getErrorFlag();

        static void setErrorFlag(bool);

    private:
        EnvPtr globalEnv_;
        static bool errorFlag;
    };
    inline bool Interpreter::getErrorFlag() { return errorFlag; }

}

#endif //LLANGUAGE_INTERPRETER_H
