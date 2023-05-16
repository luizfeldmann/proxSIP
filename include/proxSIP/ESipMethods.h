#ifndef _ESIPMETHODS_H_
#define _ESIPMETHODS_H_

#include "proxSIPExports.h"

//! Verbs for SIP requests
enum class ESipMethod
{
    Unknown = 0,
    REGISTER,    //!< @copydoc c_szREGISTER
    INVITE,      //!< @copydoc c_szINVITE
    ACK,         //!< @copydoc c_szACK
    CANCEL,      //!< @copydoc c_szCANCEL
    BYE,         //!< @copydoc c_szBYE
    OPTIONS,     //!< @copydoc c_szOPTIONS
};

extern PROXSIP_API const char* c_szSipMethodREGISTER;    //!< For registering contact information
extern PROXSIP_API const char* c_szSipMethodINVITE;      //!< Starts a call attempt
extern PROXSIP_API const char* c_szSipMethodACK;         //!< Call accepted
extern PROXSIP_API const char* c_szSipMethodCANCEL;      //!< Cancelled before ACK
extern PROXSIP_API const char* c_szSipMethodBYE;         //!< For terminating sessions
extern PROXSIP_API const char* c_szSipMethodOPTIONS;     //!< For querying servers about their capabilities

//! Converts a method to a string
PROXSIP_API const char* SipGetMethodStr(ESipMethod);

//! Parses a string into a method
PROXSIP_API ESipMethod SipGetMethodEnum(const char*);

#endif