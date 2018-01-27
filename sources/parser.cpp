
#include <iostream>
#include "../include/parser.h"
#include "../util/error.h"

namespace cen
{

    bool Parser::errorFlag = false;

    void Parser::setErrorFlag(bool flag) { errorFlag = flag; }

    Parser::Parser(Scanner &scanner) : scanner_(scanner) { scanner.next(); }

    VecExprASTPtr Parser::parse()
    {
        VecExprASTPtr vec;
        while (!validateToken(TokenValue::END_OF_FILE) && !Parser::getErrorFlag())
        {
            ExprASTPtr expp = parseStatement();
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

        Token token = scanner_.getToken();

        switch (token.getTokenValue()) {
            case TokenValue::IF:
                return parseIfStatement();
            case TokenValue::WHILE:
                return parseWhileStatement();
            case TokenValue::VAR:
                return parseVariableDefinitionStatement();
            case TokenValue::PRINT:
                return parsePrintStatement();
            case TokenValue::INPUT:
                return parseInputStatement();
            case TokenValue::BREAK:
            case TokenValue::CONTINUE:
            case TokenValue::RETURN:
                return parseFlowControllerStatement();
            case TokenValue::IDENTIFIER:
                return parseVariableUse();
            case TokenValue::DEF:
                return parseGlobalFunctionStatement();
            default:
                errorSyntax("未知的表达式开始 '" + token.getStrValue() + "'\t" + token.getTokenLocation().toString());
        }
        return nullptr;
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
                    case TokenValue::TRUE:
                    case TokenValue::FALSE:
                        return parseBool();
                    case TokenValue::DEF:
                        return parseAnonymousFunctionStatement();
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
        expectToken(TokenValue::STRING, "需要一个字符串", true);
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
        else if (token.getTokenValue() == TokenValue::INTEGER)
        {
            int num = std::strtol(token.getStrValue().c_str(), nullptr, 10);
            expr = std::make_unique<IntegerNumExprAST>(num, token.getTokenLocation());
        }
        else
        {
            errorSyntax("非法的数字类型 '" + token.getStrValue() + "'\t" + token.getTokenLocation().toString());
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
        expectToken(TokenValue::RIGHT_PAREN, "括号未匹配", true);
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
        expectToken(TokenValue::LEFT_BRACE, "块语句的开始需要一个 '{'", true);

        auto blok = std::make_unique<BlockAST>(loc);
        while (!validateToken(TokenValue::RIGHT_BRACE)
               && !validateToken(TokenValue::END_OF_FILE))
        {
            if (auto stat = parseStatement())
            {
                blok->addAST(std::move(stat));
            }
        }
        expectToken(TokenValue::RIGHT_BRACE, "块语句的结束需要一个 '}'", true);
        return blok;
    }



    ExprASTPtr Parser::parseIfStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();
        expectToken(TokenValue::IF, "'if' 关键字未找到", true);

        ExprASTPtr condition = parseParen();
        if (!condition)
        {
            errorSyntax("if 的条件语句未找到:" + lok.toString());
            return nullptr;
        }
        ExprASTPtr then = parseBlock();
        if (!then)
        {
            errorSyntax("if语句的语句块未找到: " + scanner_.getToken().getTokenLocation().toString());
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
        expectToken(TokenValue::WHILE, "'while' 关键字未找到", true);

        ExprASTPtr condition = parseParen();
        if (!condition)
        {
            errorSyntax("while的条件语句未找到 : " + lok.toString());
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
        expectToken(TokenValue::VAR, "'var' 关键字未找到", true);

        auto tok = scanner_.getToken();
        expectToken(TokenValue::IDENTIFIER, "未识别的变量名", true);

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

        expectToken(TokenValue::SEMICOLON, "';' 未找到", true);
        return std::make_unique<VariableDefinitionStatementAST>(std::move(lhs), std::move(rhs), tok.getTokenLocation());
    }



    ExprASTPtr Parser::parseVariableUse()
    {
        Token tok = scanner_.getToken();
        expectToken(TokenValue::IDENTIFIER, "未找到变量名", true);

        if (validateToken(TokenValue::ASSIGN, true))
        {
            VariableASTPtr lhs = std::make_unique<VariableAST>(tok.getStrValue());

            ExprASTPtr rhs = parseExpression();
            if (!rhs)
            {
                errorSyntax("赋值运算符的右侧没有发现表达式:" + scanner_.getToken().getTokenLocation().toString());
                return nullptr;
            }
            expectToken(TokenValue::SEMICOLON, "';'未找到", true);
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
//        if (!expectToken(TokenValue::INPUT, true))
//        {
//            errorSyntax("'input' not found:" + lok.toString());
//            return nullptr;
//        }
//
//        if (!expectToken(TokenValue::IDENTIFIER))
//        {
//            errorSyntax("需要一个变量名字" + lok.toString());
//            return nullptr;
//        }

        // todo


        return nullptr;
    }



    ExprASTPtr Parser::parsePrintStatement()
    {
        Token token = scanner_.getToken();
        expectToken(TokenValue::PRINT, "'print' 关键字未找到", true);
        ExprASTPtr exp = parseExpression();
        if (!exp) {
            errorSyntax("print语句没有发现需要打印的表达式:" + token.getTokenLocation().toString());
        }
        expectToken(TokenValue::SEMICOLON, "';'未找到", true);
        return std::make_unique<PrintStatementAST>(std::move(exp));
    }


    ExprASTPtr Parser::parseForStatement()
    {
        TokenLocation lok = scanner_.getToken().getTokenLocation();

        expectToken(TokenValue::FOR, "for 关键字未找到", true);
        expectToken(TokenValue::LEFT_BRACE, "for 语句的左括号未找到", true);


        // todo

        expectToken(TokenValue::RIGHT_BRACE, "for 的条件语句未找到");

        ExprASTPtr body = parseBlock();

        // todo

        return nullptr;
    }


    ExprASTPtr Parser::parseFlowControllerStatement()
    {
        TokenValue tokenValue = scanner_.getToken().getTokenValue();
        TokenLocation toklocn = scanner_.getToken().getTokenLocation();
        scanner_.next();

        expectToken(TokenValue::SEMICOLON, "; 未找到", true);

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


    ExprASTPtr Parser::parseGlobalFunctionStatement()
    {
        ExprASTPtr fun = parseFunctionStatement();

        // 存放(文件)全局函数

        if (!validateToken(TokenValue::END_OF_FILE)) {
            return parseStatement();
        } else {
            return nullptr;
        }
    }


    ExprASTPtr Parser::parseFunctionStatement()
    {
        using namespace std;

        TokenLocation defLok = scanner_.getToken().getTokenLocation();
        expectToken(TokenValue::DEF, "'def' 关键字未找到:" + defLok.toString(), true);
        expectToken(TokenValue::IDENTIFIER, true);

        Token fun = scanner_.getToken();
        vector<string> param;
        expectToken(TokenValue::LEFT_PAREN, true);
        if (validateToken(TokenValue::IDENTIFIER))
        {
            param.push_back(std::move(scanner_.getToken().getStrValue()));
            scanner_.next();
            while (validateToken(TokenValue::COMMA, true))
            {
                expectToken(TokenValue::IDENTIFIER, "参数列表的逗号后需要另一个变量名称");
                param.push_back(std::move(scanner_.getToken().getStrValue()));
                scanner_.next();
            }
        }
        expectToken(TokenValue::RIGHT_PAREN, "需要匹配参数列表的右括号", true);

        BlockASTPtr funBody = parseBlock();
        if (!funBody) {
            errorSyntax(fun.getStrValue() + "函数的函数体未找到:" + fun.getTokenLocation().toString());
        }
        return std::make_unique<FunAST>(std::move(fun.getStrValue()), std::move(param), std::move(funBody), fun.getTokenLocation());
    }


    ExprASTPtr Parser::parseAnonymousFunctionStatement()
    {
        using namespace std;

        TokenLocation defLok = scanner_.getToken().getTokenLocation();
        expectToken(TokenValue::DEF, "'def' 关键字未找到:" + defLok.toString(), true);

        vector<string> param;
        expectToken(TokenValue::LEFT_PAREN, true);
        if (validateToken(TokenValue::IDENTIFIER))
        {
            param.push_back(std::move(scanner_.getToken().getStrValue()));
            scanner_.next();
            while (validateToken(TokenValue::COMMA, true))
            {
                expectToken(TokenValue::IDENTIFIER, "参数列表的逗号后需要另一个变量名称");
                param.push_back(std::move(scanner_.getToken().getStrValue()));
                scanner_.next();
            }
        }
        expectToken(TokenValue::RIGHT_PAREN, "需要匹配参数列表的右括号", true);

        BlockASTPtr funBody = parseBlock();
        if (!funBody) {
            errorSyntax("匿名函数的函数体未找到:" + defLok.toString());
        }
        return std::make_unique<AnonymousFunAST>(std::move(param), std::move(funBody), defLok);
    }



}