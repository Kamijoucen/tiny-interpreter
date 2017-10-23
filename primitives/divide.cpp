
#include "divide.h"
#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{
    ValuePtr Divide::apply(const ValuePtr &v1, const ValuePtr &v2)
    {
        // todo
        ValueType t1 = v1->getType();
        ValueType t2 = v2->getType();
        if (t1 == Int && t2 == Int)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<IntValue>(l->value_ / r->value_);
        }

        if (t1 == Float && t2 == Float)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ / r->value_);
        }

        if (t1 == Float && t2 == Int)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ / r->value_);
        }

        if (t1 == Int && t2 == Float)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ / r->value_);
        }
        return nullptr;
    }

    ValueType Divide::typeCheck(const ValuePtr &v1, const ValuePtr &v2)
    {
        if (v1->getType() == Int && v2->getType() == Int)
        {
            return ValueType::INT;
        }
        else
        {
            return ValueType::FLOAT;
        }
    }
}