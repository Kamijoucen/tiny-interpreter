
#include "../util/error.h"
#include "greater.h"
#include "util.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{
    ValueType Greater::typeCheck(const ValuePtr &v1, const ValuePtr &v2)
    {
        return ValueType::BOOL;
    }

    ValuePtr Greater::apply(const ValuePtr &v1, const ValuePtr &v2)
    {
        ValueType t1 = v1->getType();
        ValueType t2 = v2->getType();

        // todo 类型检查

        if (t1 == Int && t2 == Int)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ > r->value_);
        }

        if (t1 == Float && t2 == Float)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ > r->value_);
        }

        if (t1 == Float && t2 == Int)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ > r->value_);
        }

        if (t1 == Int && t2 == Float)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<BoolValue>(l->value_ > r->value_);
        }
        return nullptr;
    }
}
