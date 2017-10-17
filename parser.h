
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "scanner.h"
#include "ast.h"

namespace lr
{

class Parser {
public:
    ExprASTPtr parsePrimary();

private:
};

}



#endif //LLANGUAGE_PARSER_H
