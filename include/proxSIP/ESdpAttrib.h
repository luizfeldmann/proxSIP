#ifndef _ESDPATTRIB_H_
#define _ESDPATTRIB_H_

#include "proxSIPExports.h"

//! Standardized types of attributes for SDP
enum class ESdpAttrib
{
    Other = 0,  //!< The attribute is not known to the standard
    cat,        //!< Dot-separated hierarchical category of the session
    keywds,     //!< To assist identifying wanted sessions based on keywords describing the purpose
    tool,       //!< Name and version number of the tool used to create the session description
    ptime,      //!< Length of time in milliseconds represented by the media in a packet
    maxptime,   //!< Maximum amount of media that can be encapsulated in each packet, in milliseconds
    rtpmap,     //!< Maps from an RTP payload type number to an encoding name denoting the payload format
    recvonly,   //!< Tools should be started in receive-only mode where applicable
    sendrecv,   //!< Tools should be started in send and receive mode
    sendonly,   //!< Tools should be started in send-only mode
    inactive,   //!< Tools should be started in inactive mode
    orient,     //!< Orientation of a the workspace
    type,       //!< Type of the conference
    charset,    //!< Character set to be used to display the session name and information
    sdplang,    //!< Language for the session or media description and information
    lang,       //!< Language of the session or media
    framerate,  //!< Maximum video frame rate in frames/sec
    quality,    //!< Suggestion for the quality of the encoding as an integer from 0 (worst) to 10 (best)
    fmtp,       //!< Allows parameters that are specific to a particular format to be conveyed
};

extern PROXSIP_API const char* c_szSDPcat;      //!< Text for #ESdpAttrib::cat
extern PROXSIP_API const char* c_szSDPkeywds;   //!< Text for #ESdpAttrib::keywds
extern PROXSIP_API const char* c_szSDPtool;     //!< Text for #ESdpAttrib::tool
extern PROXSIP_API const char* c_szSDPptime;    //!< Text for #ESdpAttrib::ptime
extern PROXSIP_API const char* c_szSDPmaxptime; //!< Text for #ESdpAttrib::maxptime
extern PROXSIP_API const char* c_szSDPrtpmap;   //!< Text for #ESdpAttrib::rtpmap
extern PROXSIP_API const char* c_szSDPrecvonly; //!< Text for #ESdpAttrib::recvonly
extern PROXSIP_API const char* c_szSDPsendrecv; //!< Text for #ESdpAttrib::sendrecv
extern PROXSIP_API const char* c_szSDPsendonly; //!< Text for #ESdpAttrib::sendonly
extern PROXSIP_API const char* c_szSDPinactive; //!< Text for #ESdpAttrib::inactive
extern PROXSIP_API const char* c_szSDPorient;   //!< Text for #ESdpAttrib::orient
extern PROXSIP_API const char* c_szSDPtype;     //!< Text for #ESdpAttrib::type
extern PROXSIP_API const char* c_szSDPcharset;  //!< Text for #ESdpAttrib::charset
extern PROXSIP_API const char* c_szSDPsdplang;  //!< Text for #ESdpAttrib::sdplang
extern PROXSIP_API const char* c_szSDPlang;     //!< Text for #ESdpAttrib::lang
extern PROXSIP_API const char* c_szSDPframerate;//!< Text for #ESdpAttrib::framerate
extern PROXSIP_API const char* c_szSDPquality;  //!< Text for #ESdpAttrib::quality
extern PROXSIP_API const char* c_szSDPfmtp;     //!< Text for #ESdpAttrib::fmtp

//! Converts the SDP attribute type enumeration to a string
PROXSIP_API const char* SdpGetAttribStr(ESdpAttrib);

//! Parses the SDP attribute string into the enumeration
PROXSIP_API ESdpAttrib SdpGetAttribEnum(const char*);

#endif