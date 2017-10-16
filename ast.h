
#ifndef SIMPLEL_AST_H
#define SIMPLEL_AST_H


#include "token.h"

namespace lr
{
    class ExprAST
    {
    public:
        ExprAST() = default;

        explicit ExprAST(TokenLocation loc);

        virtual ExprAST eval();

        virtual ~ExprAST() = default;
    private:
        TokenLocation tokenLocation_;
    };

    class BinaryExprAST : public ExprAST {
    public:
        BinaryExprAST() = default;

    private:
        ExprAST     left_;
        ExprAST     right_;
        TokenValue  op_;
    };

    class PrimaryExprAST : public ExprAST {
    public:
    private:
    };

    class NumberExprAST : public ExprAST
    {
    public:
    private:
    };

    class IfStatementAST : ExprAST {

    };


}

#endif //SIMPLEL_AST_H
