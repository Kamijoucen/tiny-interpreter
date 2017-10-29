
#include "less.h"
#include "util.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{
    ValueType Less::typeCheck(const ValuePtr &v1, const ValuePtr &v2)
    {
        return ValueType::BOOL;
    }

    ValuePtr Less::apply(const ValuePtr &v1, const ValuePtr &v2)
    {
        if (!isNumber(v1) || !isNumber(v2))
        {
            return nullptr;
        }
        ValueType t1 = v1->getType();
        ValueType t2 = v2->getType();

        if (t1 == Int && t2 == Int)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ < r->value_);
        }

        if (t1 == Float && t2 == Float)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ < r->value_);
        }

        if (t1 == Float && t2 == Int)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ < r->value_);
        }

        if (t1 == Int && t2 == Float)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ < r->value_);
        }
        return nullptr;
    }

}