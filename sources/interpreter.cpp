
#include "../include/interpreter.h"
#include "../include/scanner.h"
#include "../include/parser.h"

namespace lr
{
    using namespace std;

    bool Interpreter::errorFlag = false;

    Interpreter::Interpreter() : globalEnv_(nullptr)
    {
        globalEnv_ = Environment::buildInitScope();
    }

    void Interpreter::interp(const std::string &file)
    {
        Scanner scanner(file);
        unique_ptr<Parser> parser = std::make_unique<Parser>(scanner);

        EnvPtr fileScope = std::make_shared<Environment>(globalEnv_);

        VecExprASTPtr ast = parser->parse();

        if (!Parser::getErrorFlag())
        {
            for (auto iter = ast.begin(), end = ast.end(); iter != end && !getErrorFlag();)
            {
                (*iter++)->eval(fileScope);
            }
        }
    }

    void Interpreter::interp(const std::vector<std::string> &files)
    {

    }

    void Interpreter::setErrorFlag(bool flag) {
        errorFlag = flag;
    }

}
