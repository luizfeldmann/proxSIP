#include "ESdpAttrib.h"
#include <map>

const char* c_szSDPcat          = "cat";
const char* c_szSDPkeywds       = "keywds";
const char* c_szSDPtool         = "tool";
const char* c_szSDPptime        = "ptime";
const char* c_szSDPmaxptime     = "maxptime";
const char* c_szSDPrtpmap       = "rtpmap";
const char* c_szSDPrecvonly     = "recvonly";
const char* c_szSDPsendrecv     = "sendrecv";
const char* c_szSDPsendonly     = "sendonly";
const char* c_szSDPinactive     = "inactive";
const char* c_szSDPorient       = "orient";
const char* c_szSDPtype         = "type";
const char* c_szSDPcharset      = "charset";
const char* c_szSDPsdplang      = "sdplang";
const char* c_szSDPlang         = "lang";
const char* c_szSDPframerate    = "framerate";
const char* c_szSDPquality      = "quality";
const char* c_szSDPfmtp         = "fmtp";

#define FILL_MAP(PAIR) \
    PAIR(cat) \
    PAIR(keywds) \
    PAIR(tool) \
    PAIR(ptime) \
    PAIR(maxptime) \
    PAIR(rtpmap) \
    PAIR(recvonly) \
    PAIR(sendrecv) \
    PAIR(sendonly) \
    PAIR(inactive) \
    PAIR(orient) \
    PAIR(type) \
    PAIR(charset) \
    PAIR(sdplang) \
    PAIR(lang) \
    PAIR(framerate) \
    PAIR(quality) \
    PAIR(fmtp) \
    // end

const char* SdpGetAttribStr(ESdpAttrib eType)
{
    #define ENUM_TO_STR(X) {ESdpAttrib::X, c_szSDP##X},

    static const std::map<ESdpAttrib, const char*> theMap
    {
        FILL_MAP(ENUM_TO_STR)
    };

    const char* sType = nullptr;
    auto itFind = theMap.find(eType);

    if (theMap.cend() != itFind)
        sType = itFind->second;

    return sType;
}

ESdpAttrib SdpGetAttribEnum(const char* sType)
{
    struct strless {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };

    #define STR_TO_ENUM(X) {c_szSDP##X, ESdpAttrib::X},

    static const std::map<const char*, ESdpAttrib, strless> theMap
    {
        FILL_MAP(STR_TO_ENUM)
    };

    ESdpAttrib eType = ESdpAttrib::Other;
    auto itFind = theMap.find(sType);

    if (theMap.cend() != itFind)
        eType = itFind->second;

    return eType;
}