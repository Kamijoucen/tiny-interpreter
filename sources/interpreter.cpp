
#include "../include/interpreter.h"
#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/exception.h"
#include <iostream>

namespace cen
{
    using namespace std;

    bool Interpreter::errorFlag = false;

    Interpreter::Interpreter() : globalEnv_(Environment::buildInitScope()) {}

    void Interpreter::interp(const std::string &file)
    {
        try {
            Scanner scanner(file);
            unique_ptr<Parser> parser = std::make_unique<Parser>(scanner);

            EnvPtr fileScope = std::make_shared<Environment>(globalEnv_);

            VecExprASTPtr ast = parser->parse();
            for (auto iter = ast.begin(), end = ast.end(); iter != end && !getErrorFlag();) {
                (*iter++)->eval(fileScope);
            }

        } catch (const FileAccessError &ferr) {
            std::cerr << file + " 无法访问，请检查文件是否正确" << std::endl;
            std::cerr << ferr.what() << std::endl;
        } catch (const SyntaxError &serr) {
            std::cerr << "------------------------------语法错误------------------------------" << std::endl;
            std::cerr << serr.what() << std::endl;
        } catch (...) {
            std::cerr << "未知的异常!" << std::endl;
            throw;
        }

    }

    void Interpreter::interp(const std::vector<std::string> &files)
    {

    }

    void Interpreter::setErrorFlag(bool flag) {
        errorFlag = flag;
    }

}
