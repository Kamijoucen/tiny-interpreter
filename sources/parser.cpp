
#include <iostream>
#include "../include/parser.h"
#include "../util/error.h"

namespace lr
{

    bool Parser::errorFlag = false;

    void Parser::setErrorFlag(bool flag) { errorFlag = flag; }

    Parser::Parser(Scanner &scanner) : scanner_(scanner) { scanner.next(); }

    VecExprASTPtr Parser::parse()
    {
        VecExprASTPtr vec;
        while (!validateToken(TokenValue::END_OF_FILE) && !Parser::getErrorFlag())
        {
            ExprASTPtr expp = parsePrimary();
            if (!expp)
            {
                errorSyntax("解析错误");
                return vec;
            }
            vec.push_back(std::move(expp));
        }
        return vec;
    }


    ExprASTPtr Parser::parseStatement() {

        // todo 语句

        return lr::ExprASTPtr();
    }

    ExprASTPtr Parser::parsePrimary()
    {
        TokenType   tokenType  = scanner_.getToken().getTokenType();
        TokenValue  tokenValue = scanner_.getToken().getTokenValue();

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
                    case TokenValue::PRINT:
                        return parsePrintStatement();
                    case TokenValue::INPUT:
                        return parseInputStatement();
                    case TokenValue::BREAK:
                    case TokenValue::CONTINUE:
                    case TokenValue::RETURN:
                        return parseFlowControllerStatement();
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
                        return parseVariableUse();
                    case TokenValue::STRING:
                        return parseString();
                    default:
                        return nullptr;
                }
            default:
                return nullptr;
        }
    }


    ExprASTPtr Parser::parseString()
    {
        Token token = scanner_.getToken();
        if (!expectToken(TokenValue::STRING, true))
        {
            errorSyntax("需要一个字符串:" + token.getTokenLocation().toString());
            return nullptr;
        }
        return std::make_unique<StringAST>(token.getStrValue(), token.getTokenLocation());
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
            auto curOp    = scanner_.getToken();
            auto opMate   = scanner_.getDic().lookup(curOp.getStrValue());
            int  curOpPre = std::get<2>(opMate);

            if (curOpPre < precedence)
            {
                return lhs;
            }
            if (curOp.getTokenType() != TokenType::OPERATORS)
            {
                errorSyntax("不支持该操作符:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }
            scanner_.next();

            ExprASTPtr rhs  = parsePrimary();
            // next op
            auto nextOp     = scanner_.getToken();
            auto nextOpMate = scanner_.getDic().lookup(nextOp.getStrValue());
            int  nextOpPre  = std::get<2>(nextOpMate);

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
            errorSyntax("块语句的开始需要一个 '{'" + loc.toString());
            return nullptr;
        }
        auto blok = std::make_unique<BlockAST>(loc);

        while (!validateToken(TokenValue::RIGHT_BRACE)
               && !validateToken(TokenValue::END_OF_FILE))
        {
            if (auto stat = parsePrimary())
            {
                blok->addAST(std::move(stat));
            }
        }

        if (!expectToken(TokenValue::RIGHT_BRACE, true))
        {
            errorSyntax("块语句的结束需要一个 '}'" + loc.toString());
            return nullptr;
        }
        return blok;
    }



    ExprASTPtr Parser::parseIfStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();

        if (!expectToken(TokenValue::IF, true))
        {
            errorSyntax("'if' 关键字未找到:" + lok.toString());
            return nullptr;
        }
        ExprASTPtr condition = parseParen();

        if (!condition)
        {
            errorSyntax("if 的条件语句未找到:" + lok.toString());
            return nullptr;
        }

        if (!expectToken(TokenValue::LEFT_BRACE))
        {
            errorSyntax("if block '{' not found:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        ExprASTPtr then = parseBlock();

        if (!then)
        {
            errorSyntax("if block not found:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        ExprASTPtr elsethen = nullptr;

        if (validateToken(TokenValue::ELSE, true))
        {
            elsethen = parseBlock();
        }

        return std::make_unique<IfStatementAST>(std::move(condition), std::move(then), std::move(elsethen), lok);
    }


    ExprASTPtr Parser::parseWhileStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();

        if (!expectToken(TokenValue::WHILE, true))
        {
            errorSyntax("'while' not found:" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        ExprASTPtr condition = parseParen();

        if (!condition)
        {
            errorSyntax("parse error while condition is null : " + lok.toString());
            return nullptr;
        }

        BlockASTPtr body = parseBlock();

        if (!body)
        {
            errorSyntax("parse error while body is null : " + lok.toString());
            return nullptr;
        }

        return std::make_unique<WhileStatementAST>(std::move(condition), std::move(body), std::move(lok));
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
            errorSyntax("';' not found :" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        return std::make_unique<VariableDefinitionStatementAST>(std::move(lhs), std::move(rhs), tok.getTokenLocation());
    }



    ExprASTPtr Parser::parseVariableUse()
    {
        Token tok = scanner_.getToken();

        if (!expectToken(TokenValue::IDENTIFIER, true))
        {
            errorSyntax("未找到变量名字" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        if (validateToken(TokenValue::ASSIGN, true))
        {
            VariableASTPtr lhs = std::make_unique<VariableAST>(tok.getStrValue());

            ExprASTPtr rhs = parseExpression();

            if (!rhs)
            {
                errorSyntax("赋值运算符的右侧没有发现表达式:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }

            if (!expectToken(TokenValue::SEMICOLON, true))
            {
                errorSyntax("没有找到语句结束分号:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }
            return std::make_unique<VariableAssignStatementAST>(std::move(lhs), std::move(rhs), tok.getTokenLocation());
        }
        else
        {
            return std::make_unique<VariableUseStatementAST>(tok.getStrValue(), tok.getTokenLocation());
        }
    }



    ExprASTPtr Parser::parseInputStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();
        if (!expectToken(TokenValue::INPUT, true))
        {
            errorSyntax("'input' not found:" + lok.toString());
            return nullptr;
        }

        if (!expectToken(TokenValue::IDENTIFIER))
        {
            errorSyntax("需要一个变量名字" + lok.toString());
            return nullptr;
        }

        // todo


        return nullptr;
    }



    ExprASTPtr Parser::parsePrintStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();
        if (!expectToken(TokenValue::PRINT, true))
        {
            errorSyntax("'print' not found:" + lok.toString());
            return nullptr;
        }
        ExprASTPtr exp = parseExpression();

        if (!expectToken(TokenValue::SEMICOLON, true))
        {
            errorSyntax("';' not found :" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }
        return std::make_unique<PrintStatementAST>(std::move(exp));
    }


    ExprASTPtr Parser::parseForStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();
        if (!expectToken(TokenValue::FOR, true))
        {
            errorSyntax("'for' not found:" + lok.toString());
            return nullptr;
        }

        if (!expectToken(TokenValue::LEFT_BRACE, true))
        {
            errorSyntax("for condition left brace not found" + lok.toString());
            return nullptr;
        }

        VecExprASTPtr exps = parseMoreExpression(TokenValue::SEMICOLON);

        // todo

        if (!expectToken(TokenValue::RIGHT_BRACE))
        {
            errorSyntax("for condition right brace not found" + lok.toString());
            return nullptr;
        }

        ExprASTPtr body = parseBlock();

        // todo

        return nullptr;
    }


    VecExprASTPtr Parser::parseMoreExpression(const TokenValue &sep)
    {

        return lr::VecExprASTPtr();
    }


    ExprASTPtr Parser::parseFlowControllerStatement()
    {
        TokenValue tokenValue = scanner_.getToken().getTokenValue();
        TokenLocation toklocn = scanner_.getToken().getTokenLocation();
        scanner_.next();

        if (!expectToken(TokenValue::SEMICOLON, true))
        {
            errorSyntax("';' not found :" + scanner_.getToken().getTokenLocation().toString());
            return nullptr;
        }

        switch (tokenValue)
        {
            case TokenValue::BREAK:
                return std::make_unique<BreakAST>(toklocn);
            case TokenValue::CONTINUE:
                return std::make_unique<ContinueAST>(toklocn);
            case TokenValue::RETURN:
                return std::make_unique<ReturnAST>(toklocn);
            default:
                return nullptr;
        }
    }


    bool Parser::expectToken(TokenValue val, bool next)
    {
        if (scanner_.getToken().getTokenValue() != val)
        {
            auto tok = scanner_.getToken();
            errorSyntax("unknown token:" + tok.getStrValue() + "" + tok.getTokenLocation().toString());
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