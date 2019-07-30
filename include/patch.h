#ifndef PATCH_H_INCLUDED
#define PATCH_H_INCLUDED
#include <string>
#include <sstream>

namespace patch
{
    template<typename T>
    std::string to_string(const T& n)
    {
        std::ostringstream ss;
        ss<<n;
        return ss.str();
    }
}

#endif // PATCH_H_INCLUDED
