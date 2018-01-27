
#include "../include/value.h"
#include "../include/ast.h"

namespace cen
{

    NoneValue::NoneValuePtr NoneValue::nonePtr_ = std::make_shared<NoneValue>();

    VoidValue::VoidValuePtr VoidValue::voidPtr_ = std::make_shared<VoidValue>();

    FloatValue::FloatValue(float val) : value_(val) {}

    IntValue::IntValue(int val) : value_(val) {}

    BoolValue::BoolValue(bool val) : value_(val) {}

    StringValue::StringValue(const std::string &str) : value_(str) {}

    Closure::Closure(Closure::BlockAST &body) : body_(body) {}
}