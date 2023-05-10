#ifndef _CSIPPARSER_H_
#define _CSIPPARSER_H_

#include "ISIPRequest.h"
#include "ISIPResponse.h"

//! Possible results for parser error
enum class EParserResult
{
    Success,
    UnexpectedEnd,
    BadLineEnding,
    BadMethod,
    BadTarget,
    BadVersion,
    BadFieldName,
};

//! Parses SIP requests and responses
class PROXSIP_API CSipParser
{
public:
    //! Parses a raw buffer into a SIP request
    static EParserResult ParseRequest(const char* szData, size_t uSize, ISIPRequest& Request);

    //! Parses a raw buffer into a SIP response
    static EParserResult ParseResponse(const char* szData, size_t uSize, ISIPResponse& Response);
};

#endif