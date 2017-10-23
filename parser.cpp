
#include "parser.h"
#include <iostream>

namespace lr
{

    Parser::Parser(Scanner &scanner) : scanner_(scanner) { scanner.next(); }

    ExprASTPtr lr::Parser::parsePrimary()
    {
        TokenType   tokenType   = scanner_.getToken().getTokenType();
        TokenValue  tokenValue  = scanner_.getToken().getTokenValue();

        switch (tokenType)
        {
            case TokenType::KEYWORDS:
                switch (tokenValue)
                {
                    case TokenValue::IF:
                        return parseIfStatement();
                    case TokenValue::WHILE:
                        return parseWhileStatement();
                    default:
                        return nullptr;
                }
            case TokenType::DELIMITER:
                switch (tokenValue)
                {
                    case TokenValue::LEFT_PAREN:
                        return parseParen();
                    case TokenValue::LEFT_BRACE:
                        return parseBlock();
                    default:
                        return nullptr;
                }
            case TokenType::NUMBER:
                return parseNumber();
            default:
                return nullptr;
        }
    }

    ExprASTPtr Parser::parseIdentifier()
    {
        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parseNumber()
    {
        Token token = scanner_.getToken();
        scanner_.next();
        if (token.getTokenValue() == TokenValue::FLOAT)
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
        if (scanner_.getToken().getTokenValue() != TokenValue::RIGHT_PAREN) {
            std::cout << "括号不匹配" << std::endl;
            return nullptr;
        }
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
            auto curOp      = scanner_.getToken();
            auto opMate     = scanner_.getDic().lookup(curOp.getStrValue());
            int  curOpPre   = std::get<2>(opMate);

            if (curOpPre < precedence)
            {
                return lhs;
            }
            if (curOp.getTokenType() != TokenType::OPERATORS)
            {
                // todo
                std::cout << "op error:" << curOp.getStrValue() << std::endl;
                return nullptr;
            }
            scanner_.next();

            ExprASTPtr  rhs         = parsePrimary();
            auto        nextOp      = scanner_.getToken();
            auto        nextOpMate  = scanner_.getDic().lookup(nextOp.getStrValue());
            int         nextOpPre   = std::get<2>(nextOpMate);

            if (curOpPre < nextOpPre)
            {
                rhs = parseBinOpRHS(std::move(rhs), curOpPre + 1);
                if (!rhs)
                {
                    return nullptr;
                }
            }
            lhs = std::make_unique<BinaryExprAST>(std::move(lhs), std::move(rhs), curOp.getTokenValue(), curOp.getTokenLocation());
        }
    }

    BlockASTPtr Parser::parseBlock()
    {
        return lr::BlockASTPtr();
    }

    ExprASTPtr Parser::parse()
    {
        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parseIfStatement()
    {
        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parseWhileStatement()
    {
        return lr::ExprASTPtr();
    }

}