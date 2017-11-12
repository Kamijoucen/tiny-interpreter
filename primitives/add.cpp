#include "add.h"
#include "../util/error.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{
    ValuePtr Add::apply(const ValuePtrVec &vec, const TokenLocation &lok)
    {
        if (vec.size() != 2)
        {
            errorSyntax("'+'必须作用于两个以上的值");
            return nullptr;
        }

        ValuePtr  v1 = vec[0];
        ValuePtr  v2 = vec[1];
        ValueType t1 = v1->getType();
        ValueType t2 = v2->getType();
        if (t1 == Int && t2 == Int)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<IntValue>(l->value_ + r->value_);
        }

        if (t1 == Float && t2 == Float)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (t1 == Float && t2 == Int)
        {
            const auto l = static_cast<FloatValue*>(v1.get());
            const auto r = static_cast<IntValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (t1 == Int && t2 == Float)
        {
            const auto l = static_cast<IntValue*>(v1.get());
            const auto r = static_cast<FloatValue*>(v2.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        errorSyntax("类型错误:" + lok.toString());
        return nullptr;
    }

    ValueType Add::typeCheck(const ValuePtrVec &vec)
    {
        if (vec.size() != 2)
        {
            errorSyntax("'+'必须作用于两个以上的值");
            return ValueType::UNKNOWN;
        }

        // todo xixixi
        return ValueType::UNKNOWN;
    }
}
