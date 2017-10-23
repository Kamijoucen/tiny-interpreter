
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "scanner.h"
#include "ast.h"

namespace lr
{

class Parser
{
public:

    ExprASTPtr  parse();

    ExprASTPtr  parsePrimary();

    ExprASTPtr  parseBinOpRHS(ExprASTPtr lhs, int precedence);

    ExprASTPtr  parseExpression();

    ExprASTPtr  parseParen();

    ExprASTPtr  parseNumber();

    ExprASTPtr  parseIdentifier();

    ExprASTPtr  parseIfStatement();

    ExprASTPtr  parseWhileStatement();

    BlockASTPtr parseBlock();

public:
    explicit Parser(Scanner&);

private:
    Scanner &scanner_;
};


}



#endif //LLANGUAGE_PARSER_H
