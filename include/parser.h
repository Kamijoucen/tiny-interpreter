
#ifndef LLANGUAGE_PARSER_H
#define LLANGUAGE_PARSER_H

#include "exception.h"
#include "scanner.h"
#include "ast.h"

namespace cen
{

    using FunMatePtr = std::tuple<std::string, GlobalExprASTPtr >;

    class Parser
    {
    public:

        VecExprASTPtr parse();

        ExprASTPtr    parseStatement();

        BlockASTPtr   parseBlock();

        ExprASTPtr    parsePrimary();

        ExprASTPtr    parseBinOpRHS(ExprASTPtr lhs, int precedence);

        ExprASTPtr    parseExpression();

        ExprASTPtr    parseParen();

        ExprASTPtr    parseString();

        ExprASTPtr    parseBool();

        ExprASTPtr    parseNumber();

        ExprASTPtr    parseIfStatement();

        ExprASTPtr    parseWhileStatement();

        ExprASTPtr    parseForStatement();

        ExprASTPtr    parseVariableDefinitionStatement();

        ExprASTPtr    parseIdentifier();

        ExprASTPtr    parseGlobalFunctionStatement();   // 不需要将全局函数加入到语法树中

        ExprASTPtr    parseAnonymousFunctionStatement();

        FunMatePtr    parseFunctionStatement();

        ExprASTPtr    parsePrintStatement();

        ExprASTPtr    parseInputStatement();

        ExprASTPtr    parseFlowControllerStatement();

    public:
        explicit Parser(Scanner&);

        static void setErrorFlag(bool flag);

        inline static bool getErrorFlag();

    private:

        inline void expectToken(TokenValue val, bool next = false);

        inline void expectToken(TokenValue val, const std::string &msg, bool next = false);

        inline void expectToken(TokenValue val, const char *msg, bool next = false);

        inline bool validateToken(TokenValue val, bool next = false);

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


    inline void Parser::expectToken(TokenValue val, bool next) { expectToken(val, "", next); }

    inline void Parser::expectToken(TokenValue val, const std::string &msg, bool next) {
        if (scanner_.getToken().getTokenValue() != val) {
            auto tok = scanner_.getToken();
            throw SyntaxError(msg + "\t非预期的符号: " + tok.getStrValue() + "\t" + tok.getTokenLocation().toString());
        }
        if (next) scanner_.next();
    }

    inline bool Parser::validateToken(TokenValue val, bool next) {
        if (scanner_.getToken().getTokenValue() != val) return false;
        if (next) scanner_.next();
        return true;
    }

    inline void Parser::expectToken(TokenValue val, const char *msg, bool next) {
        expectToken(val, std::move(static_cast<std::string>(msg)), next);
    }

}

#endif //LLANGUAGE_PARSER_H
