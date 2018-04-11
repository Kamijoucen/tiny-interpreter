
#ifndef LLANGUAGE_RESULT_H
#define LLANGUAGE_RESULT_H

#include <memory>
#include <ostream>
#include <vector>
#include <string>

namespace cen
{
    class BlockAST;
    class Value;
    class Environment;
    class AnonymousFunAST;

    using EnvPtr = std::shared_ptr<Environment>;
    using BlockASTPtr = std::unique_ptr<BlockAST>;

    using ValuePtr = std::shared_ptr<Value>;

    enum class ValueType
    {
        VOID,
        INT,
        FLOAT,
        STRING,
        BOOL,
        ANY,
        NONE,
        OP,
        NULLED,
        CLOSURE,
        ARRAY,
        UNKNOWN
    };


    class Value
    {
    public:
		virtual ValueType getType() const = 0;

        virtual std::string toString() const = 0;

    public:
        virtual ~Value() = default;

    private:
    };



    class ArrayValue : public Value
    {
    public:
    public:
    private:
    };



    class BoolValue : public Value
    {
    public:
        ValueType getType() const override;

    public:
        explicit BoolValue(bool val);

        inline std::string toString() const override;

        bool value_;

    private:
        const ValueType type_ = ValueType::BOOL;
    };
    inline ValueType BoolValue::getType() const { return type_; }
    inline std::string BoolValue::toString() const { return value_ ? "true" : "false"; }



    class IntValue : public Value
    {
    public:
        ValueType getType() const override;

    public:
        explicit IntValue(int val);

        inline std::string toString() const override;

        int value_;

    private:
        const ValueType type_ = ValueType::INT;
    };
    inline ValueType IntValue::getType() const { return type_; }
    inline std::string IntValue::toString() const { return std::to_string(value_); }



    class FloatValue : public Value
    {
    public:
        ValueType getType() const override;

    public:
        explicit FloatValue(float val);

        inline std::string toString() const override;

        float value_;
    private:
        const ValueType type_ = ValueType::FLOAT;
    };
    inline ValueType FloatValue::getType() const { return type_; }
    inline std::string FloatValue::toString() const { return std::to_string(value_); }



    class StringValue : public Value
    {
    public:
        inline ValueType getType() const override;

        inline std::string toString() const override;

    public:
        explicit StringValue(const std::string &str);

        std::string value_;
    };
    inline ValueType StringValue::getType() const { return ValueType::STRING; }
    inline std::string StringValue::toString() const { return value_; }



    class NoneValue : public Value {
    public:
        NoneValue() = default;

        using NoneValuePtr = std::shared_ptr<NoneValue>;

        inline ValueType getType() const override;

        inline std::string toString() const override;

        static inline NoneValuePtr instance();

    private:
        static NoneValuePtr nonePtr_;
    };
    inline std::string NoneValue::toString() const { return "NONE"; }
    inline ValueType NoneValue::getType() const { return ValueType::NONE; }
    inline NoneValue::NoneValuePtr NoneValue::instance() { return nonePtr_; }



    class VoidValue : public Value
    {
    public:
        VoidValue() = default;

        using VoidValuePtr = std::shared_ptr<VoidValue>;

        inline ValueType getType() const override;

        inline std::string toString() const override;

        static inline VoidValuePtr instance();

    private:
        static VoidValuePtr voidPtr_;

    };
    inline std::string VoidValue::toString() const { return "void"; }
    inline ValueType VoidValue::getType() const { return ValueType::VOID; }
    inline VoidValue::VoidValuePtr VoidValue::instance() { return voidPtr_; }


    class Closure : public Value
    {
    public:
        Closure(std::vector<std::string> param, BlockASTPtr& body, EnvPtr &closureEnv);

        inline ValueType getType() const override;

        inline std::string toString() const override;

        BlockASTPtr &body_;
        EnvPtr &closureEnv_;
        std::vector<std::string> param_;

    };
    inline ValueType Closure::getType() const { return ValueType::CLOSURE; }
    inline std::string Closure::toString() const { return "function"; }


}
#endif //LLANGUAGE_RESULT_H
