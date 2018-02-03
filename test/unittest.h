#ifndef LLANGUAGE_UNITTEST_H
#define LLANGUAGE_UNITTEST_H

#include <gtest/gtest.h>
#include <iostream>
#include "../include/environment.h"
#include "../util/util.h"
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/value.h"
#include "../include/ast.h"
#include "../include/exception.h"

using namespace cen;

TEST(breaktest, t)
{
    cen::ExprASTPtr p = std::make_unique<BreakAST>();
    ASSERT_EQ(typeid(BreakAST) == typeid(*p), true);
}

TEST(eval, fz)
{
    std::string f("../Resource/fz.l");
    Scanner scanner(f);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    EnvPtr env = Environment::buildInitScope();
    for (auto &stat : vec)
    {
        stat->eval(env);
    }
}

TEST(parse, parseAll)
{
    std::string f("../Resource/vars.l");
    Scanner scanner(f);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    ASSERT_EQ(vec.size(), 6);
}


TEST(compExpr, expr) {
    std::string a("../Resource/comp.l");
    Scanner scanner(a);
    Parser parser(scanner);
    ExprASTPtr val = parser.parseExpression();
    ASSERT_TRUE(val != nullptr);
    ValuePtr vp = val->eval(Environment::buildInitScope());
    ASSERT_TRUE(vp != nullptr);
    if (vp->getType() == ValueType::FLOAT) {
        FloatValue *fv = static_cast<FloatValue *>(vp.get());
        ASSERT_EQ(12, fv->value_);
    } else {
        IntValue *fv = static_cast<IntValue *>(vp.get());
        ASSERT_EQ(12, fv->value_);
    }
}

TEST(varExpr, expr)
{
    std::string a("../Resource/var.l");
    Scanner scanner(a);
    Parser parser(scanner);
    ExprASTPtr exp = parser.parsePrimary();
    ASSERT_TRUE(exp != nullptr);
    VariableDefinitionStatementAST *asa = dynamic_cast<VariableDefinitionStatementAST *>(exp.get());
    ASSERT_TRUE(asa != nullptr);
}

TEST(scannerType, scanner) {
    std::string a("../Resource/fun.l");
    Scanner scanner(a);
    scanner.next();
    while (scanner.getToken().getTokenValue() != TokenValue::END_OF_FILE) {
        std::cout << scanner.getToken().getTokenValue() << std::endl;
        scanner.next();
    }
}

TEST(eval, whiletest)
{
    std::string a("../Resource/while.l");
    Scanner scanner(a);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    EnvPtr env = Environment::buildInitScope();
    for (auto &stat : vec)
    {
        stat->eval(env);
    }
}

TEST(eval, string)
{
    std::string a("../Resource/str.l");
    Scanner scanner(a);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    EnvPtr env = Environment::buildInitScope();
    for (auto &stat : vec)
    {
        stat->eval(env);
    }
}


TEST(eval, iftest)
{
    std::string a("../Resource/iftest.l");
    Scanner scanner(a);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    EnvPtr env = Environment::buildInitScope();
    for (auto &stat : vec)
    {
        stat->eval(env);
    }
}

TEST(eval, flowctest)
{
    std::string a("../Resource/flowc.l");
    Scanner scanner(a);
    Parser parser(scanner);
    VecExprASTPtr vec = parser.parse();
    EnvPtr env = Environment::buildInitScope();
    for (auto &stat : vec)
    {
        if (!Parser::getErrorFlag()) {
            stat->eval(env);
        }
    }
}

TEST(iter, iter)
{
    Interpreter iter;
    iter.interp("../Resource/flowc.l");
}

TEST(eval, print)
{
    Interpreter iter;
    iter.interp("../Resource/print.l");
}


TEST(eval, fun)
{
    try {
        Scanner scanner("../Resource/fun.l");
        Parser p(scanner);
        p.parseFunctionStatement();
    } catch (const FileAccessError &error) {
        std::cout << error.what() << std::endl;
    }
}

TEST(fun, call)
{
    Interpreter interpreter;
    interpreter.interp("../Resource/call.l");
}

TEST(fun, closure)
{
    Interpreter interpreter;
    interpreter.interp("../Resource/closure.l");
}

TEST(fun, digui)
{
    Interpreter interpreter;
    interpreter.interp("../Resource/fun1.l");
}

#endif //LLANGUAGE_UNITTEST_H
