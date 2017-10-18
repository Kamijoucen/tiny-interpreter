
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "scanner.h"
#include "ast.h"

namespace lr
{

class Parser
{
public:

    ExprASTPtr parse();

    ExprASTPtr parsePrimary();

    ExprASTPtr parseBinOpRHS(ExprASTPtr lhs, int precedence);

    ExprASTPtr parseExpression();

    ExprASTPtr parseParen();

    ExprASTPtr parseBlock();

    ExprASTPtr parseNumber();

    ExprASTPtr parseIdentifier();

public:
    explicit Parser(Scanner&);

private:
    Scanner &scanner_;
};


}



#endif //LLANGUAGE_PARSER_H
