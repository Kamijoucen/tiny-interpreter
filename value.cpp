
#include "value.h"

namespace lr
{
    FloatValue::FloatValue(float val) : value_(val) {}

    IntValue::IntValue(int val) : value_(val) {}

    BoolValue::BoolValue(bool val) : value_(val) {}

    StringValue::StringValue(const std::string &str) : value_(str) {}
}