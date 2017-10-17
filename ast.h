
#ifndef SIMPLEL_AST_H
#define SIMPLEL_AST_H


#include "token.h"
#include "memory"

namespace lr
{

    class ExprAST;
    class NumberExprAST;

    using ExprASTPtr        = std::unique_ptr<ExprAST>;
    using NumberExprASTPtr  = std::unique_ptr<NumberExprAST>;

    class ExprAST {
    public:
        ExprASTPtr eval();

        TokenLocation getTokenLocation();

    public:
        ExprAST() = default;

        explicit ExprAST(TokenLocation loc);

        virtual ~ExprAST() = default;

    protected:
        TokenLocation tokenLocation_;
    };

    inline TokenLocation ExprAST::getTokenLocation() { return tokenLocation_; }


    class BinaryExprAST : public ExprAST
    {
    public:

    public:
        BinaryExprAST() = default;

        BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &tokenLocation);

    private:
        ExprASTPtr  left_;
        ExprASTPtr  right_;
        TokenValue  op_;
    };

    class NumberExprAST : public ExprAST
    {
    public:
    private:
    };

    class IfStatementAST : public ExprAST
    {

    };

    class WhileStatementAST : public ExprAST
    {

    };

    class ForStatementAST : public ExprAST
    {

    };

    class DoWhileStatementAST : public ExprAST
    {

    };

}

#endif //SIMPLEL_AST_H
