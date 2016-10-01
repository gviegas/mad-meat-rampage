/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef AUX_HXX
#define AUX_HXX

#include <string>
#include <iostream>

namespace aux {
struct Hasher {
    template<class T> 
    std::size_t operator()(T t) const { 
        return static_cast<std::size_t>(t); 
    }
};

#if defined(__unix__) || defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>

inline std::string getBasePath() {
    char buffer[2048];
    if(getcwd(buffer, sizeof(buffer)) != NULL) {
        return std::string(buffer) + '/';
    }
    return nullptr;
}

#endif
} // namespace aux

#endif