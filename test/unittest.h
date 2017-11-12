#ifndef LLANGUAGE_UNITTEST_H
#define LLANGUAGE_UNITTEST_H

#include <gtest/gtest.h>
#include <iostream>
#include "../environment.h"
#include "test.h"
#include "../parser.h"

using namespace lr;


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
    std::string a("../Resource/var.l");
    Scanner scanner(a);
    scanner.next();
    while (scanner.getToken().getTokenValue() != TokenValue::END_OF_FILE) {
        std::cout << scanner.getToken().getTokenValue() << std::endl;
        scanner.next();
    }
}


#endif //LLANGUAGE_UNITTEST_H
