#ifndef _SNSCANF_H_
#define _SNSCANF_H_

//! Safe function _snscanf_s is not available in GCC, so fall back to POSIX
#ifndef _MSC_VER
    #include <string>

    #define _snscanf_s(P, L, F, ...) sscanf(std::string(P, L).c_str(), F, __VA_ARGS__)
    #define _MAX_PATH 260
#endif // _MSC_VER

#endif // _SNSCANF_H_
