#include "../../include/primitives/posi.h"
#include "../../include/token.h"
#include "../../util/error.h"

namespace cen
{

    ValuePtr Posi::apply(const ValuePtrVec &vec, const TokenLocation &lok)
    {
        if (vec.size() != 1)
        {
            errorInterp("取正操作符后必须跟一个表达式:" + lok.toString());
            return nullptr;
        }

        ValuePtr expVal = vec[0];
        ValueType type = expVal->getType();
        switch (type) {
            case ValueType::INT:
            case ValueType::FLOAT:
            default:
                errorInterp("取正运算符只能作用于数字类型:" + lok.toString());
                return nullptr;
        }
    }

    ValueType Posi::typeCheck(const ValuePtrVec &vec) {
        return ValueType::UNKNOWN;
    }

    ValueType Posi::getType() const {
        return ValueType::OP;
    }

    std::string Posi::toString() const {
        return "+";
    }


}
