#include "add.h"

#define Int     lr::ValueType::INT
#define Float   lr::ValueType::FLOAT

namespace lr
{
    Add::Add(const ValuePtr &v1, const ValuePtr &v2) : v1_(v1), v2_(v2) {}

    ValuePtr Add::apply()
    {
        ValueType t1 = v1_->getType();
        ValueType t2 = v2_->getType();
        if (t1 == Int && t2 == Int)
        {
            const auto l = static_cast<IntValue*>(v1_.get());
            const auto r = static_cast<IntValue*>(v2_.get());
            return std::make_shared<IntValue>(l->value_ + r->value_);
        }

        if (t1 == Float && t2 == Float)
        {
            const auto l = static_cast<FloatValue*>(v1_.get());
            const auto r = static_cast<FloatValue*>(v2_.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (t1 == Float && t2 == Int)
        {
            const auto l = static_cast<FloatValue*>(v1_.get());
            const auto r = static_cast<IntValue*>(v2_.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }

        if (t1 == Int && t2 == Float)
        {
            const auto l = static_cast<IntValue*>(v1_.get());
            const auto r = static_cast<FloatValue*>(v2_.get());
            return std::make_shared<FloatValue>(l->value_ + r->value_);
        }
        return nullptr;
    }

    ValueType Add::typeCheck()
    {
        if (v1_->getType() == Int && v2_->getType() == Int)
        {
            return ValueType::INT;
        }
        else
        {
            return ValueType::FLOAT;
        }
    }
}
