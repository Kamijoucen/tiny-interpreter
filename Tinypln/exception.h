#ifndef PL_EXCEPTION_H
#define PL_EXCEPTION_H

#include <stdexcept>

namespace cen
{

    struct FileAccessError : public std::runtime_error
    {
        explicit FileAccessError(const std::string &__arg) noexcept;
    };


    struct SyntaxError : public std::runtime_error
    {
        explicit SyntaxError(const std::string &__arg) noexcept;
    };

}


#endif //PL_EXCEPTION_H
