
#ifndef SIMPLEL_AST_H
#define SIMPLEL_AST_H


#include "token.h"
#include "value.h"
#include <memory>
#include <vector>

namespace lr
{

    class ExprAST;
    class NumberExprAST;
    class BlockAST;

    using ExprASTPtr        = std::unique_ptr<ExprAST>;
    using NumberExprASTPtr  = std::unique_ptr<NumberExprAST>;
    using VecExprASTPtr     = std::vector<std::unique_ptr<ExprAST>>;
    using BlockASTPtr       = std::unique_ptr<BlockAST>;

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


    class BlockAST : public ExprAST
    {
    public:
        explicit BlockAST(TokenLocation &);
    public:
        ValuePtr eval() override;

        void addAST(ExprASTPtr ptr);

    private:
        VecExprASTPtr vec_;
    };
    inline void BlockAST::addAST(ExprASTPtr ptr) { vec_.push_back(std::move(ptr)); }


    class VariableAST : public ExprAST
    {
    public:
        ValuePtr eval() override;

        inline std::string getVarName() const;

    public:
        explicit VariableAST(std::string str);

    private:
        std::string varName_;
    };
    inline std::string VariableAST::getVarName() const { return varName_; }


    class AssignStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override;

    public:
        AssignStatementAST(ExprASTPtr lhs, ExprASTPtr rhs, const TokenLocation &location);

    private:
        ExprASTPtr lhs_;
        ExprASTPtr rhs_;
    };


    class BinaryExprAST : public ExprAST
    {
    public:
        ValuePtr eval() override;

    public:
        BinaryExprAST() = default;

        BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tokenValue, const TokenLocation &tokenLocation);

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
        inline float getVal() const;

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
        IfStatementAST(ExprASTPtr condition, ExprASTPtr thenPart_);

    public:
        ValuePtr eval() override {}

    private:
        ExprASTPtr condition_;
        ExprASTPtr thenPart_;
        ExprASTPtr elsePart_;
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
