
#ifndef SIMPLEL_AST_H
#define SIMPLEL_AST_H

#include "environment.h"
#include "token.h"
#include "value.h"
#include <memory>
#include <vector>

namespace cen
{

    /*
     * 变量的赋值应该基于拷贝而不是仅仅拷贝智能指针。  基本类型的赋值 a = b, a,b就应该是两个
     * 独立变量了。 如果仅仅是拷贝只能指针仍然是引用同一个值。！！！！！！！
     *
     */
    class ExprAST;
    class NumberExprAST;
    class BlockAST;
    class VariableAST;
    class FunAST;
    class CallAST;
    class NameAST;

    using GlobalExprASTPtr = std::shared_ptr<FunAST>;
    using ExprASTPtr       = std::unique_ptr<ExprAST>;
    using NumberExprASTPtr = std::unique_ptr<NumberExprAST>;
    using BlockASTPtr      = std::unique_ptr<BlockAST>;
    using VariableASTPtr   = std::unique_ptr<VariableAST>;
    using NameASTPtr       = std::unique_ptr<NameAST>;
    using VecExprASTPtr    = std::vector<std::unique_ptr<ExprAST>>;

    class ExprAST
    {
    public:
        virtual ValuePtr eval(EnvPtr env) = 0;

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
        ValuePtr eval(EnvPtr env) override;

        void addAST(ExprASTPtr ptr);

        inline const VecExprASTPtr& getBody() const;

    private:
        VecExprASTPtr vec_;
    };
    inline void BlockAST::addAST(ExprASTPtr ptr) { vec_.push_back(std::move(ptr)); }
    inline const VecExprASTPtr& BlockAST::getBody() const { return vec_; }


    class VariableAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override;

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
        ValuePtr eval(EnvPtr env) override;

    public:
        VariableDefinitionStatementAST(VariableASTPtr lhs, ExprASTPtr rhs, TokenLocation lok);

    private:
        VariableASTPtr  lhs_;
        ExprASTPtr      rhs_;
    };



    class VariableAssignStatementAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override;

    public:
        VariableAssignStatementAST(NameASTPtr lhs, ExprASTPtr rhs, const TokenLocation &lok);

    private:
        NameASTPtr  lhs_;
        ExprASTPtr  rhs_;
    };



    class VariableUseStatementAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override;

    public:
        explicit VariableUseStatementAST(const std::string &varname, TokenLocation lok);

    private:
        std::string varname_;
    };



    class UnaryExprAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override;

    public:
        UnaryExprAST() = default;

        UnaryExprAST(ExprASTPtr hs, TokenValue tv, const TokenLocation &lok);

    private:
        ExprASTPtr hs_;
        TokenValue op_;
    };



    class BinaryExprAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override;

    public:
        BinaryExprAST() = default;

        BinaryExprAST(ExprASTPtr left, ExprASTPtr right, TokenValue tv, const TokenLocation &lok);

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
		ValuePtr eval(EnvPtr env) override;

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

		ValuePtr eval(EnvPtr env) override;
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

        ValuePtr eval(EnvPtr env) override;

    private:
        bool value_;
    };
    inline bool BoolAST::getVal() const { return value_; }



    class StringAST : public ExprAST
    {
    public:
        StringAST(std::string str, const TokenLocation &lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        std::string value_;
    };



    class IfStatementAST : public ExprAST
    {
    public:
        IfStatementAST(ExprASTPtr condition, ExprASTPtr thenPart, ExprASTPtr elsePart, const TokenLocation &lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        ExprASTPtr condition_;
        ExprASTPtr thenPart_;
        ExprASTPtr elsePart_;
    };



    class WhileStatementAST : public ExprAST
    {
    public:
        WhileStatementAST(ExprASTPtr condion, BlockASTPtr body, TokenLocation lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        ExprASTPtr  condition_;
        BlockASTPtr body_;
    };



    class DoWhileStatementAST : public ExprAST
    {
    public:
        DoWhileStatementAST(ExprASTPtr condition, BlockASTPtr body, TokenLocation lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        ExprASTPtr condition_;
        BlockASTPtr body_;
    };



    class ForStatementAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override {}

    private:
    };



    class DoWhileStatementAST : public ExprAST
    {
    public:
        ValuePtr eval(EnvPtr env) override {}


    private:
    };


    // todo 简单实现方便调试
    class PrintStatementAST : public ExprAST
    {
    public:
        explicit PrintStatementAST(ExprASTPtr val);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        ExprASTPtr val_;
    };


    class BreakAST : public ExprAST
    {
    public:
        BreakAST() = default;

        explicit BreakAST(const TokenLocation &tokenLocation);

    public:
        ValuePtr eval(EnvPtr env) override;
    };


    class ContinueAST : public ExprAST
    {
    public:
        ContinueAST() = default;

        explicit ContinueAST(const TokenLocation &lok);

    public:
        ValuePtr eval(EnvPtr env) override;
    };


    class ReturnAST : public ExprAST
    {
    public:
        ReturnAST(ExprASTPtr ast, TokenLocation lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        ExprASTPtr returnExp_;
    };


    class FunAST : public ExprAST
    {
    public:
        friend class CallAST;

    public:
        FunAST(std::string name, std::vector<std::string> param, BlockASTPtr body, const TokenLocation &lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        std::vector<std::string> param_;
        std::string name_;
        BlockASTPtr body_;
    };


    class AnonymousFunAST : public ExprAST
    {
    public:
        friend class CallAST;

    public:
        AnonymousFunAST(std::vector<std::string> param, std::vector<std::string> envParam, BlockASTPtr body, TokenLocation lok);

    public:
        ValuePtr eval(EnvPtr env) override;

    private:
        std::vector<std::string> param_;
        std::vector<std::string> envParam_;
        BlockASTPtr body_;
        EnvPtr closureEnv_;
    };

    class NameAST : public ExprAST
    {
    public:
        NameAST(std::string name, TokenLocation lok);

    public:
        ValuePtr eval(EnvPtr env) override;

        const std::string &getName() const;

    private:
        std::string name_;
    };


    class CallAST : public ExprAST
    {
    public:
        CallAST(std::string name, std::vector<std::vector<ExprASTPtr>> params, TokenLocation lok);

    public:
        ValuePtr eval1(EnvPtr env);

        ValuePtr eval(EnvPtr env) override;

    private:
        std::string name_;
        std::vector<std::vector<ExprASTPtr>> params_;
    };


}

#endif //SIMPLEL_AST_H
