
#ifndef SIMPLEL_AST_H
#define SIMPLEL_AST_H


#include "token.h"
#include "value.h"
#include <memory>

namespace lr
{

    class ExprAST;
    class NumberExprAST;

    using ExprASTPtr        = std::unique_ptr<ExprAST>;
    using NumberExprASTPtr  = std::unique_ptr<NumberExprAST>;

    class ExprAST
    {
    public:
        virtual ValuePtr eval() { return nullptr; }

        inline TokenLocation getTokenLocation();

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

        ValuePtr eval() override;

    public:
        BinaryExprAST() = default;
        BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &tokenLocation);
        BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, TokenLocation &&tokenLocation);

    private:
        ValuePtr add();

        ValuePtr minus();

        ValuePtr multiply();

        ValuePtr divide();

    private:
        ExprASTPtr  left_;
        ExprASTPtr  right_;
        TokenValue  op_;
    };

    class IntegerNumExprAST : public ExprAST
    {
    public:
        inline int getVal() const;
    public:
		ValuePtr eval() override;

        IntegerNumExprAST(int num, TokenLocation tokenLocation);
    private:
        int value_;
    };
    inline int IntegerNumExprAST::getVal() const { return value_; }

    class FloatNumExprAST : public ExprAST
    {
    public:
        inline float getVal() const ;
    public:
		ValuePtr eval() override;

        FloatNumExprAST(float num, TokenLocation tokenLocation);
    private:
        float value_;
    };
    inline float FloatNumExprAST::getVal() const { return value_; }

    class IfStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override {}
    private:
    };

    class WhileStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override {}
    private:
    };

    class ForStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override {}
    private:
    };

    class DoWhileStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override {}
    private:
    };

}

#endif //SIMPLEL_AST_H
