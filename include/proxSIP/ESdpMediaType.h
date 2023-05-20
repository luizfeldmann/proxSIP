#ifndef _ESDPMEDIATYPE_H_
#define _ESDPMEDIATYPE_H_

#include "proxSIPExports.h"

//! Enumeration of possible types of media
enum class ESdpMediaType
{
    Unknown = 0,
    Audio,
    Video,
    Text,
    Application,
    Message,
};

extern PROXSIP_API const char* c_szSdpAudio;        //!< String for #ESdpMediaType::Audio
extern PROXSIP_API const char* c_szSdpVideo;        //!< String for #ESdpMediaType::Video
extern PROXSIP_API const char* c_szSdpText;         //!< String for #ESdpMediaType::Text
extern PROXSIP_API const char* c_szSdpApplication;  //!< String for #ESdpMediaType::Application
extern PROXSIP_API const char* c_szSdpMessage;      //!< String for #ESdpMediaType::Message

//! Converts the SDP media type enumeration to a string
PROXSIP_API const char* SdpGetMediaTypeStr(ESdpMediaType);

//! Parses the SDP media type string into the enumeration
PROXSIP_API ESdpMediaType SdpGetMediaTypeEnum(const char*);

#endif