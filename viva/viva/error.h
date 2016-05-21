#pragma once

#include <stdexcept>

namespace viva
{
    class Error : public std::runtime_error
    {
    public:
        const char* function;

        // fun should be a function that throws that error
        Error(const char* fun, const char* msg) :
            runtime_error(msg), function(fun) {}
    };
}