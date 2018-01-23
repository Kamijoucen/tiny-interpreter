
#include "../include/interpreter.h"
#include "../include/scanner.h"
#include "../include/parser.h"
#include <iostream>

namespace cen
{
    using namespace std;

    bool Interpreter::errorFlag = false;

    void Interpreter::interp(const std::string &file)
    {
        try {
            Scanner scanner(file);
            unique_ptr<Parser> parser = std::make_unique<Parser>(scanner);
            VecExprASTPtr program = parser->parse();

            EnvPtr fileScope = Environment::buildInitScope();
            for (auto iter = program.begin(), end = program.end(); iter != end && !getErrorFlag();) {
                (*iter++)->eval(fileScope);
            }

        } catch (const FileAccessError &ferr) {
            std::cerr << file + " 无法访问，请检查文件是否正确" << std::endl;
            std::cerr << ferr.what() << std::endl;
        } catch (const SyntaxError &serr) {
            std::cerr << "--------------------语法错误--------------------" << std::endl;
            std::cerr << serr.what() << std::endl;
        } catch (...) {
            std::cerr << "未知的异常!" << std::endl;
            throw;
        }

    }

    void Interpreter::setErrorFlag(bool flag) {
        errorFlag = flag;
    }

}
