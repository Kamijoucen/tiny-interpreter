
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
    class VariableAST;

    using ExprASTPtr        = std::unique_ptr<ExprAST>;
    using NumberExprASTPtr  = std::unique_ptr<NumberExprAST>;
    using BlockASTPtr       = std::unique_ptr<BlockAST>;
    using VariableASTPtr    = std::unique_ptr<VariableAST>;
    using VecExprASTPtr     = std::vector<std::unique_ptr<ExprAST>>;

    class ExprAST
    {
    public:
        virtual ValuePtr eval() {};

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



    class VariableDefinitionStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override;

    public:
        VariableDefinitionStatementAST(VariableASTPtr lhs, ExprASTPtr rhs, const TokenLocation &location);

    private:
        VariableASTPtr  lhs_;
        ExprASTPtr      rhs_;
    };



    class VariableAssignStatementAST : public ExprAST
    {
    public:
        ValuePtr eval() override;

    public:
        VariableAssignStatementAST(VariableASTPtr lhs, ExprASTPtr rhs, const TokenLocation &location);

    private:
        VariableASTPtr  lhs_;
        ExprASTPtr      rhs_;
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
        FloatNumExprAST(float num, TokenLocation tokenLocation);

    public:
        inline float getVal() const;

		ValuePtr eval() override;
    private:
        float value_;
    };
    inline float FloatNumExprAST::getVal() const { return value_; }



    class BoolAST : public ExprAST
    {
    public:
        BoolAST(bool val, const TokenLocation &lok);

    public:
        inline bool getVal() const;

        ValuePtr eval() override;
    private:
        bool value_;
    };
    inline bool BoolAST::getVal() const { return value_; }



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
