
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "scanner.h"
#include "ast.h"

namespace cen
{

    class Parser
    {
    public:

        VecExprASTPtr parse();

        ExprASTPtr    parseStatement();

        BlockASTPtr   parseBlock();

        ExprASTPtr    parsePrimary();

        ExprASTPtr    parseBinOpRHS(ExprASTPtr lhs, int precedence);

        ExprASTPtr    parseExpression();

        VecExprASTPtr parseMoreExpression(const TokenValue &sep);

        ExprASTPtr    parseParen();

        ExprASTPtr    parseString();

        ExprASTPtr    parseBool();

        ExprASTPtr    parseNumber();

        ExprASTPtr    parseIfStatement();

        ExprASTPtr    parseWhileStatement();

        ExprASTPtr    parseForStatement();

        ExprASTPtr    parseVariableDefinitionStatement();

        ExprASTPtr    parseVariableUse();

        ExprASTPtr    parseFunctionDefinitionStatement();

        ExprASTPtr    parsePrintStatement();

        ExprASTPtr    parseInputStatement();

        ExprASTPtr    parseFlowControllerStatement();

    public:
        explicit Parser(Scanner&);

        static void setErrorFlag(bool flag);

        inline static bool getErrorFlag();

    private:

        void expectToken(TokenValue val, bool next = false);

        void expectToken(TokenValue val, const std::string &msg, bool next = false);

        void expectToken(TokenValue val, const char *msg, bool next = false);

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
