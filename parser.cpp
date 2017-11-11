
#include "parser.h"
#include "util/error.h"
#include <iostream>

namespace lr
{

    bool Parser::errorFlag = false;

    void Parser::setErrorFlag(bool flag) { errorFlag = flag; }

    Parser::Parser(Scanner &scanner) : scanner_(scanner) { scanner.next(); }

    VecExprASTPtr Parser::parse()
    {
        VecExprASTPtr vec;
        while (!validateToken(TokenValue::END_OF_FILE))
        {
            ExprASTPtr expp = parsePrimary();
            if (!expp)
            {
                errorSyntax("parseError");
                return vec;
            }
            vec.push_back(std::move(expp));
        }
        return vec;
    }

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
                    case TokenValue::VAR:
                        return parseVariableDefinitionStatement();
                    case TokenValue::TRUE:
                    case TokenValue::FALSE:
                        return parseBool();
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
            case TokenType::OPERATORS:
            case TokenType::NUMBER:
                return parseNumber();
            case TokenType::UNRESERVED:
                switch (tokenValue)
                {
                    case TokenValue::IDENTIFIER:
                        return parseVariableAssignStatement();
                    default:
                        return nullptr;
                }
            default:
                return nullptr;
        }
    }


    ExprASTPtr Parser::parseNumber()
    {
        bool isNeg = false;
        if (validateToken(TokenValue::MINUS, true))
        {
            isNeg = true;
        }
        Token token = scanner_.getToken();
        scanner_.next();

        ExprASTPtr expr = nullptr;
        if (token.getTokenValue() == TokenValue::FLOAT)
        {
            float num = static_cast<float>(std::strtod(token.getStrValue().c_str(), nullptr));
            expr = std::make_unique<FloatNumExprAST>(num, token.getTokenLocation());
        }
        else
        {
            int num = std::strtol(token.getStrValue().c_str(), nullptr, 10);
            expr = std::make_unique<IntegerNumExprAST>(num, token.getTokenLocation());
        }
        if (isNeg)
        {
            // todo 处理负数
        }
        return expr;
    }

    ExprASTPtr Parser::parseParen()
    {
        scanner_.next();    // eat (
        ExprASTPtr ptr = parseExpression();
        if (!expectToken(TokenValue::RIGHT_PAREN, true))
        {
            errorSyntax("括号未匹配:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        return ptr;
    }

    ExprASTPtr Parser::parseExpression()
    {
        ExprASTPtr ptr = parsePrimary();
        if (!ptr)
        {
            return nullptr;
        }
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
                errorSyntax("不是有效的操作符:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }
            scanner_.next();

            ExprASTPtr  rhs         = parsePrimary();
            // next op
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
        auto loc = scanner_.getToken().getTokenLocation();

        if (!expectToken(TokenValue::LEFT_BRACE, true))
        {
            return nullptr;
        }

        auto blok = std::make_unique<BlockAST>(loc);

        while (validateToken(TokenValue::RIGHT_BRACE, true))
        {
            if (auto stat = parsePrimary())
            {
                blok->addAST(std::move(stat));
            }
            else
            {
                return nullptr;
            }
        }

        if (!expectToken(TokenValue::RIGHT_BRACE, true))
        {
            return nullptr;
        }
        return blok;
    }

    ExprASTPtr Parser::parseIfStatement()
    {
        if (expectToken(TokenValue::IF, true))
        {
            errorSyntax("'if' not found:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        ExprASTPtr condition = parseExpression();

        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parseWhileStatement()
    {
        return lr::ExprASTPtr();
    }



    ExprASTPtr Parser::parseVariableDefinitionStatement()
    {
        if (!expectToken(TokenValue::VAR, true))
        {
            errorSyntax("未知的标识符" + scanner_.getToken().getStrValue());
            return nullptr;
        }
        auto tok = scanner_.getToken();

        if (!expectToken(TokenValue::IDENTIFIER, true))
        {
            errorSyntax("错误的标识符" + scanner_.getToken().getStrValue());
            return nullptr;
        }

        VariableASTPtr lhs = std::make_unique<VariableAST>(tok.getStrValue());

        ExprASTPtr rhs = nullptr;
        if (validateToken(TokenValue::ASSIGN, true))
        {
            rhs = parseExpression();
            if (!rhs)
            {
                errorSyntax("赋值运算符的右侧没有发现表达式:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }
        }

        if (!expectToken(TokenValue::SEMICOLON, true))
        {
            errorSyntax("没有找到结束符:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        return std::make_unique<VariableDefinitionStatementAST>(std::move(lhs), std::move(rhs), tok.getTokenLocation());
    }



    ExprASTPtr Parser::parseVariableAssignStatement()
    {
        if (!expectToken(TokenValue::IDENTIFIER))
        {
            errorSyntax("未找到变量名字" + scanner_.getToken().getTokenLocation().toString());
        }

        TokenLocation lok = scanner_.getToken().getTokenLocation();
        VariableASTPtr variablePtr = std::make_unique<VariableAST>(scanner_.getToken().getStrValue());

        if (!expectToken(TokenValue::ASSIGN, true))
        {
            errorSyntax("没有找到赋值运算符" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        ExprASTPtr exp = parseExpression();

        if (!exp)
        {
            errorSyntax("赋值运算符的右侧没有发现表达式:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        if (!expectToken(TokenValue::SEMICOLON, true))
        {
            errorSyntax("没有找到结束符:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        return std::make_unique<VariableAssignStatementAST>(std::move(variablePtr), std::move(exp), lok);
    }


    bool Parser::expectToken(TokenValue val, bool next)
    {
        if (scanner_.getToken().getTokenValue() != val)
        {
            auto tok = scanner_.getToken();
            errorSyntax("出现意料之外的标识符 '" + tok.getStrValue() + "'" + tok.getTokenLocation().toString());
            return false;
        }
        if (next)
        {
            scanner_.next();
        }
        return true;
    }

    bool Parser::validateToken(TokenValue val, bool next)
    {
        if (scanner_.getToken().getTokenValue() != val)
        {
            return false;
        }
        if (next)
        {
            scanner_.next();
        }
        return true;
    }


}