#ifndef _CSIPSERIALIZER_H_
#define _CSIPSERIALIZER_H_

//! Serializes SIP requests and responses
class PROXSIP_API CSipSerializer
{
public:
    //! Serializes a SIP request into a buffer
    static bool SerializeRequest(const char* szData, size_t uSize, ISIPRequest& Request);

    //! Serializes a SIP response into a buffer
    static bool SerializeResponse(const char* szData, size_t uSize, ISIPResponse& Response);
};

#endif