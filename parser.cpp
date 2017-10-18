
#include "parser.h"
#include "dictionary.h"
#include <cstdlib>
#include <iostream>

namespace lr
{

    Parser::Parser(Scanner &scanner) : scanner_(scanner) { scanner.next(); }

    ExprASTPtr lr::Parser::parsePrimary()
    {
        TokenType   tokenType   = scanner_.getToken().getTokenType();
        TokenValue  tokenValue  = scanner_.getToken().getTokenValue();

        if (tokenValue == TokenValue::LEFT_PAREN)
        {
            return parseParen();
        }

        if (tokenType == TokenType::IDENTIFIER)
        {
            return parseIdentifier();
        }

        if (tokenType == TokenType::NUMBER)
        {
            return parseNumber();
        }

        return nullptr;
    }

    ExprASTPtr Parser::parseIdentifier()
    {
        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parseNumber()
    {
        Token token = scanner_.getToken();
        scanner_.next();
        if (token.getTokenValue() == TokenValue::INTEGER)
        {
            float num = static_cast<float>(std::strtod(token.getStrValue().c_str(), nullptr));
            return std::make_unique<FloatNumExprAST>(num, token.getTokenLocation());
        }
        else
        {
            int num = std::strtol(token.getStrValue().c_str(), nullptr, 10);
            return std::make_unique<IntegerNumExprAST>(num, token.getTokenLocation());
        }
    }

    ExprASTPtr Parser::parseParen()
    {
        scanner_.next();    // eat (
        ExprASTPtr ptr = parseExpression();
        scanner_.next();    // eat )
        return ptr;
    }

    ExprASTPtr Parser::parseExpression()
    {
        ExprASTPtr ptr = parsePrimary();
        return parseBinOpRHS(std::move(ptr), 1);
    }

    ExprASTPtr Parser::parseBinOpRHS(ExprASTPtr lhs, int precedence)
    {
        while (true)
        {
            auto curTok = scanner_.getToken();
            if (curTok.getTokenType() != TokenType::OPERATORS)
            {
                // todo
                std::cout << "op error" << std::endl;
                return nullptr;
            }
            auto opMate     = scanner_.getDic().lookup(curTok.getStrValue());
            int  curOpPre   = std::get<2>(opMate);
            if (curOpPre < precedence)
            {
                return lhs;
            }
            scanner_.next();

            ExprASTPtr  priPtr      = parsePrimary();
            auto        nextTok     = scanner_.getToken();
            auto        nextOpMate  = scanner_.getDic().lookup(nextTok.getStrValue());
            int         nextOpPre   = std::get<2>(nextOpMate);
            if (curOpPre > nextOpPre)
            {
                priPtr = parseBinOpRHS(std::move(priPtr), curOpPre + 1);
                if (!priPtr)
                {
                    return nullptr;
                }
            }
            lhs = std::make_unique<BinaryExprAST>(std::move(lhs), std::move(priPtr), nextTok.getTokenValue(), curTok.getTokenLocation());
        }
    }

    ExprASTPtr Parser::parseBlock()
    {
        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parse()
    {
        return lr::ExprASTPtr();
    }

}