
#include <iostream>
#include "error.h"
#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

namespace lr {
    void errorToken(const std::string &msg) {
        std::cerr << "词法错误:" << msg << std::endl;
        Scanner::setErrorFlag(true);
    }

    void errorSyntax(const std::string &msg) {
        std::cerr << "语法错误: " << msg << std::endl;
        Parser::setErrorFlag(true);
    }

    void errorInterp(const std::string &msg) {
        std::cerr << "执行错误: " + msg << std::endl;
        Interpreter::setErrorFlag(true);
    }
}
