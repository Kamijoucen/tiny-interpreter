
#include "../include/value.h"
#include "../include/ast.h"
#include "../include/environment.h"

namespace cen {

    NoneValue::NoneValuePtr NoneValue::nonePtr_ = std::make_shared<NoneValue>();

    VoidValue::VoidValuePtr VoidValue::voidPtr_ = std::make_shared<VoidValue>();

    FloatValue::FloatValue(float val) : value_(val) {}

    IntValue::IntValue(int val) : value_(val) {}

    BoolValue::BoolValue(bool val) : value_(val) {}

    StringValue::StringValue(const std::string &str) : value_(str) {}

    Closure::Closure(std::vector<std::string> param, BlockASTPtr &body, EnvPtr &closureEnv) : body_(body),
                                                                                              param_(std::move(param)),
                                                                                              closureEnv_(closureEnv) {}
}