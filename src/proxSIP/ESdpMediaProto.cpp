#include "ESdpMediaProto.h"
#include <cstring>
#include <map>

const char* c_szSdpUDP      = "udp";
const char* c_szSdpRTPAVP   = "RTP/AVP";
const char* c_szSdpRTPSAVP  = "RTP/SAVP";

#define FILL_MAP(PAIR) \
    PAIR(UDP, c_szSdpUDP) \
    PAIR(RTPAVP, c_szSdpRTPAVP) \
    PAIR(RTPSAVP, c_szSdpRTPSAVP) \
    // end

const char* SdpGetMediaProtoStr(ESdpMediaProto eType)
{
    #define ENUM_TO_STR(A, B) {ESdpMediaProto::A, B},

    static const std::map<ESdpMediaProto, const char*> theMap
    {
        FILL_MAP(ENUM_TO_STR)
    };

    const char* sType = nullptr;
    auto itFind = theMap.find(eType);

    if (theMap.cend() != itFind)
        sType = itFind->second;

    return sType;
}

ESdpMediaProto SdpGetMediaProtoEnum(const char* sType)
{
    struct strless {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };

    #define STR_TO_ENUM(A, B) {B, ESdpMediaProto::A},

    static const std::map<const char*, ESdpMediaProto, strless> theMap
    {
        FILL_MAP(STR_TO_ENUM)
    };

    ESdpMediaProto eType = ESdpMediaProto::Unknown;
    auto itFind = theMap.find(sType);

    if (theMap.cend() != itFind)
        eType = itFind->second;

    return eType;
}