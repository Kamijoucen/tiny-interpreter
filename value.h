
#ifndef LLANGUAGE_RESULT_H
#define LLANGUAGE_RESULT_H

#include <memory>

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
        ANY
    };

    class Value
    {
    public:
		virtual ValueType getType() const { return ValueType::ANY;  };
        virtual ~Value() = default;
    private:
    };


    class IntValue : public Value
    {
    public:
        ValueType getType() const override;
    public:
        explicit IntValue(int val);
        int value_;
    private:
        const ValueType type_ = ValueType::INT;
    };
    inline ValueType IntValue::getType() const { return type_; }


    class FloatValue : public Value
    {
    public:
        ValueType getType() const override;
    public:
        explicit FloatValue(float val);

        float value_;
    private:
        const ValueType type_ = ValueType::FLOAT;
    };
    inline ValueType FloatValue::getType() const { return type_; }


    class BoolValue : public Value
    {
    public:
        ValueType getType() const override;
    public:
        explicit BoolValue(bool val);
        bool value_;
    private:
        const ValueType type_ = ValueType::BOOL;
    };
    inline ValueType BoolValue::getType() const { return type_; }


}
#endif //LLANGUAGE_RESULT_H
