#ifndef _PROXSIP_EXPORTS_H_
#define _PROXSIP_EXPORTS_H_

#ifdef PROXSIP_EXPORT
    #define PROXSIP_API __declspec(dllexport)
#else
    #define PROXSIP_API __declspec(dllimport)
#endif

#endif