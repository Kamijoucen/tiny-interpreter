#include "../include/exception.h"

namespace cen
{
    FileAccessError::FileAccessError(const std::string &__arg) noexcept : runtime_error(__arg) {}

    SyntaxError::SyntaxError(const std::string &__arg) noexcept : runtime_error(__arg) {}
}