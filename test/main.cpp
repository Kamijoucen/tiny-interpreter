#include <iostream>
#include "../scanner.h"
#include "../parser.h"
#include "test.h"

using namespace std;
using namespace lr;

int main()
{
    string file = "../Resource/comp.l";

    Scanner scanner(file);
    Parser parser(scanner);

    ExprASTPtr s = parser.parseExpression();
    s->eval();

    return 0;
}