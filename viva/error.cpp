#include "viva.h"

namespace viva
{
    // Viva specific excpetions.
    class Error : public std::runtime_error
    {
    public:
        const char* function;

        // Ctor.
        // fun: should be a function that throws that exception
        // msg: custom message, like what happened ?
        Error(const char* fun, const char* msg) 
            : runtime_error(msg), function(fun) 
        {
        }

        Error(const char* fun, wstring msg)
            : runtime_error(std::string(msg.begin(),msg.end()).c_str()), function(fun)
        {
        }
    };
}