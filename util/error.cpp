
#include <iostream>
#include "error.h"
#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/exception.h"

namespace cen {

    // todo
    void errorToken(const std::string &msg) {
        std::cerr << "词法错误:" << msg << std::endl;
        Scanner::setErrorFlag(true);
    }

    void errorSyntax(const std::string &msg) {
        throw SyntaxError("语法错误: " + msg);
    }

    void errorInterp(const std::string &msg) {
        std::cerr << "执行错误: " + msg << std::endl;
        Interpreter::setErrorFlag(true);
    }
}
