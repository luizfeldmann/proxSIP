#ifndef _CSIPSERIALIZER_H_
#define _CSIPSERIALIZER_H_

#include "ISIPRequest.h"
#include "ISIPResponse.h"

//! Serializes SIP requests and responses
class PROXSIP_API CSipSerializer
{
public:
    //! Serializes a SIP message
    static void SerializeMessage(const ISIPMessage& Message, IBuffer& Buffer);

    //! Serializes a SIP request
    static void SerializeRequest(const ISIPRequest& Request, IBuffer& Buffer);

    //! Serializes a SIP response
    static void SerializeResponse(const ISIPResponse& Response, IBuffer& Buffer);
};

#endif