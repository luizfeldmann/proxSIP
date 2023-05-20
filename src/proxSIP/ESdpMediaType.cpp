#include "ESdpMediaType.h"
#include <map>

const char* c_szSdpAudio        = "audio";
const char* c_szSdpVideo        = "video";
const char* c_szSdpText         = "text";
const char* c_szSdpApplication  = "application";
const char* c_szSdpMessage      = "message";

#define FILL_MAP(PAIR) \
    PAIR(Audio, c_szSdpAudio) \
    PAIR(Video, c_szSdpVideo) \
    PAIR(Text, c_szSdpText) \
    PAIR(Application, c_szSdpApplication) \
    PAIR(Message, c_szSdpMessage) \
    // end

const char* SdpGetMediaTypeStr(ESdpMediaType eType)
{
    #define ENUM_TO_STR(A, B) {ESdpMediaType::A, B},

    static const std::map<ESdpMediaType, const char*> theMap
    {
        FILL_MAP(ENUM_TO_STR)
    };

    const char* sType = nullptr;
    auto itFind = theMap.find(eType);

    if (theMap.cend() != itFind)
        sType = itFind->second;

    return sType;
}

ESdpMediaType SdpGetMediaTypeEnum(const char* sType)
{
    struct strless {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };

    #define STR_TO_ENUM(A, B) {B, ESdpMediaType::A},

    static const std::map<const char*, ESdpMediaType, strless> theMap
    {
        FILL_MAP(STR_TO_ENUM)
    };

    ESdpMediaType eType = ESdpMediaType::Unknown;
    auto itFind = theMap.find(sType);

    if (theMap.cend() != itFind)
        eType = itFind->second;

    return eType;
}