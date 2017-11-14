
#ifndef LLANGUAGE_RESULT_H
#define LLANGUAGE_RESULT_H

#include <memory>
#include <ostream>

namespace lr
{
    class Value;

    using ValuePtr = std::shared_ptr<Value>;

    enum class ValueType
    {
        VOID,
        INT,
        FLOAT,
        STRING,
        BOOL,
        ANY,
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
    inline std::string BoolValue::toString() const { return std::to_string(value_); }



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
        ValueType getType() const override;

        inline std::string toString() const override;

    public:
        explicit StringValue(const std::string &str);

        std::string value_;
    };
    inline ValueType StringValue::getType() const { return ValueType::STRING; }
    inline std::string StringValue::toString() const { return value_; }
}
#endif //LLANGUAGE_RESULT_H
