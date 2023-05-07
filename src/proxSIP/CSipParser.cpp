#include "CSipParser.h"
#include <boost/utility/string_view.hpp>

/* Request parsing */

bool CSipParser::ParseRequest(const char* szData, size_t uSize, ISIPRequest& Request)
{
    boost::string_view svMsg(szData, uSize);

    

    return false;
}

/* Response parsing */

bool CSipParser::ParseResponse(const char* szData, size_t uSize, ISIPResponse& Response)
{
    return false;
}