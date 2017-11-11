
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "scanner.h"
#include "ast.h"

namespace lr
{

    class Parser
    {
    public:

        VecExprASTPtr   parse();

        BlockASTPtr     parseBlock();

        ExprASTPtr      parsePrimary();

        ExprASTPtr      parseBinOpRHS(ExprASTPtr lhs, int precedence);

        ExprASTPtr      parseExpression();

        ExprASTPtr      parseParen();

        ExprASTPtr      parseNumber();

        ExprASTPtr      parseIfStatement();

        ExprASTPtr      parseWhileStatement();

        ExprASTPtr      parseBool();

        ExprASTPtr      parseVariableDefinitionStatement();

        ExprASTPtr      parseVariableAssignStatement();

    public:
        explicit Parser(Scanner&);

        static void setErrorFlag(bool flag);

        inline static bool getErrorFlag();

    private:

        bool expectToken(TokenValue val, bool next = false);

        bool validateToken(TokenValue val, bool next = false);

    private:
        Scanner         &scanner_;
        static bool     errorFlag;
    };

    bool Parser::getErrorFlag() { return errorFlag; }

    inline ExprASTPtr Parser::parseBool()
    {
        Token tok = scanner_.getToken();
        scanner_.next();
        return std::make_unique<BoolAST>(tok.getTokenValue() == TokenValue::TRUE, tok.getTokenLocation());
    }

}

#endif //LLANGUAGE_PARSER_H
