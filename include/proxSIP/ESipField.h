#ifndef _ESIPFIELD_H_
#define _ESIPFIELD_H_

#include "proxSIPExports.h"

//! The possible data fields in SIP messages
enum class ESipField
{
    Unknown = 0,
    Via,            //!< @copydoc c_szVia
    MaxForwards,    //!< @copydoc c_szMaxForwards
    From,           //!< @copydoc c_szFrom
    To,             //!< @copydoc c_szTo
    Contact,        //!< @copydoc c_szContact
    CallID,         //!< @copydoc c_szCallID
    CSeq,           //!< @copydoc c_szCSeq
    Expires,        //!< @copydoc c_szExpires
    ContentType,    //!< @copydoc c_szContentType
    ContentLength,  //!< @copydoc c_szContentLength
};

extern PROXSIP_API const char* c_szSipVia;
extern PROXSIP_API const char* c_szSipMaxForwards;
extern PROXSIP_API const char* c_szSipFrom;
extern PROXSIP_API const char* c_szSipTo;
extern PROXSIP_API const char* c_szSipContact;
extern PROXSIP_API const char* c_szSipCallID;
extern PROXSIP_API const char* c_szSipCSeq;
extern PROXSIP_API const char* c_szSipExpires;
extern PROXSIP_API const char* c_szSipContentType;
extern PROXSIP_API const char* c_szSipContentLength;

//! Converts a field enumeration to a string
PROXSIP_API const char* SipGetFieldStr(ESipField);

//! Converts a field name to the enumeration
PROXSIP_API ESipField SipGetFieldEnum(const char*);

#endif