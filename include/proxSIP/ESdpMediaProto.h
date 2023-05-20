#ifndef _ESDPMEDIAPROTO_
#define _ESDPMEDIAPROTO_

#include "proxSIPExports.h"

//! Denotes the media transport protocol
enum class ESdpMediaProto
{
    Unknown = 0,
    UDP,        //!< An unspecified protocol running over UDP
    RTPAVP,     //!< RTP Profile for Audio and Video Conferences with Minimal Control
    RTPSAVP,    //!< Secure Real-time Transport Protocol
};

extern PROXSIP_API const char* c_szSdpUDP;      //!< Text for #ESdpMediaProto::UDP
extern PROXSIP_API const char* c_szSdpRTPAVP;   //!< Text for #ESdpMediaProto::RTPAVP
extern PROXSIP_API const char* c_szSdpRTPSAVP;  //!< Text for #ESdpMediaProto::RTPSAVP

//! Converts the SDP media protocol enumeration to a string
PROXSIP_API const char* SdpGetMediaProtoStr(ESdpMediaProto);

//! Parses the SDP media protocol string into the enumeration
PROXSIP_API ESdpMediaProto SdpGetMediaProtoEnum(const char*);

#endif