#include "CSipParser.h"
#include <boost/utility/string_view.hpp>

/* Util */

static inline char is_token_char(char c)
{
    static char constexpr tab[] = {
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        0, 1, 0, 1,  1, 1, 1, 1,  0, 0, 1, 1,  0, 1, 1, 0, // 32
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 0, 0, // 48
        0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 1, 1, // 80
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  1, 0, 1, 0, // 112
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 128
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 144
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 160
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 176
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 192
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 208
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 224
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0  // 240
    };

    return tab[static_cast<unsigned char>(c)];
}

static inline bool is_pathchar(char c)
{
    static bool constexpr tab[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //   0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  16
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //  32
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //  48
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //  64
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //  80
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //  96
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // 112
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 128
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 144
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 160
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 176
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 192
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 208
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 224
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  // 240
    };

    return tab[static_cast<unsigned char>(c)];
}

static inline boost::string_view make_string(char const* first, char const* last)
{
    return { first, static_cast<
        std::size_t>(last - first) };
}

/* Common to both requests and responses */

//! Parse *one* field
static EParserResult ParseField(const char*& p, const char* pEnd, ISIPRequest& Request)
{
    const char* pFirst = p;

    // Find the ":" separator
    static char const* is_field_name =
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\1\0\1\1\1\1\1\0\0\1\1\0\1\1\0\1\1\1\1\1\1\1\1\1\1\0\0\0\0\0\0"
        "\0\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\0\0\0\1\1"
        "\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\0\1\0\1\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

    for (;;)
    {
        // Stop when the separator is found
        if (*p == ':')
            break;

        // Verify the field name has only valid characters
        if (!is_field_name[static_cast<unsigned char>(*p)])
        {
            return EParserResult::BadFieldName;
        }

        ++p;

        // Verify there is content *after* the name
        if (p >= pEnd)
        {
            return EParserResult::UnexpectedEnd;
        }
    }

    // Check if the field name is not empty
    if (p == pFirst)
    {
        return EParserResult::BadFieldName;
    }

    // Read the full name
    boost::string_view svName = make_string(pFirst, p);
    ++p; // eat ':'

    // Skip leading blanks
    for (; (*p == ' ' || *p == '\t') ; ++p)
    {
        if (p + 1 > pEnd)
        {
            return EParserResult::UnexpectedEnd;
        }
    }

    // First character of the value
    pFirst = p;
    boost::string_view svValue;

    // parse until CRLF
    for (;;)
    {
        if (p + 2 > pEnd)
        {
            return EParserResult::UnexpectedEnd;
        }

        if (p[0] == '\r')
        {
            // Missing LF...
            if (p[1] != '\n')
            {
                return EParserResult::BadLineEnding;
            }

            svValue = make_string(pFirst, p);

            // Skip the CRLF - end of field parsing
            p += 2;
            break;
        }

        ++p;
    }

    // Push the field into the message struct
    const auto sKey = svName.to_string();
    const auto sValue = svValue.to_string();
    Request.Fields().Insert(sKey.c_str(), sValue.c_str());

    return EParserResult::Success;
}

//! Parses all the fields
static EParserResult ParseFields(const char*& szData, const char* last, ISIPRequest& Request)
{
    EParserResult eResult = EParserResult::Success;

    for (;;)
    {
        // There must be room for at least the CRLF
        if (szData + 2 > last)
        {
            eResult = EParserResult::UnexpectedEnd;
            break;
        }

        // Blank line
        if (szData[0] == '\r')
        {
            // Missing LF...
            if (szData[1] != '\n')
            {
                eResult = EParserResult::BadLineEnding;
            }

            // End of fields section
            szData += 2;
            break;
        }

        // Read each field
        eResult = ParseField(szData, last, Request);

        if (EParserResult::Success != eResult)
            break;
    }

    return eResult;
}

//! Parse body content
static EParserResult ParseContent(const char*& szData, const char* pEnd, ISIPRequest& Request)
{
    if (pEnd > szData)
    {
        size_t uContentLength = pEnd - szData;
        Request.Content().write(szData, uContentLength);
    }
    szData = pEnd;

    return EParserResult::Success;
}

//! Parse fields and body
static EParserResult ParseMessage(const char*& szData, const char* pEnd, ISIPRequest& Request)
{
    EParserResult eStatus = ParseFields(szData, pEnd, Request);

    if (EParserResult::Success == eStatus)
        eStatus = ParseContent(szData, pEnd, Request);;

    return eStatus;
}

/* Request parsing */

//! Extracts the request method
static EParserResult ParseMethod(const char*& it, const char* pEnd, boost::string_view& result)
{
    const char* pFirst = it;

    for (;; ++it)
    {
        if (it + 1 > pEnd)
        {
            return EParserResult::UnexpectedEnd;
        }

        if (!is_token_char(*it))
            break;
    }

    if (it + 1 > pEnd)
    {
        return EParserResult::UnexpectedEnd;
    }

    if (*it != ' ')
    {
        return EParserResult::BadMethod;
    }

    if (it == pFirst)
    {
        return EParserResult::BadMethod;
    }

    result = make_string(pFirst, it++);

    return EParserResult::Success;
}

//! Extracts the request URI
static EParserResult ParseTarget(const char*& it, const char* pEnd, boost::string_view& svResult)
{
    const char* pFirst = it;

    for (;; ++it)
    {
        if (it + 1 > pEnd)
        {
            return EParserResult::UnexpectedEnd;
        }

        if (!is_pathchar(*it))
            break;
    }

    if (it + 1 > pEnd)
    {
        return EParserResult::UnexpectedEnd;
    }

    if (*it != ' ')
    {
        return EParserResult::BadTarget;
    }

    if (it == pFirst)
    {
        return EParserResult::BadTarget;
    }

    svResult = make_string(pFirst, it++);

    return EParserResult::Success;
}

//! Extract the protocol version
static EParserResult ParseVersion(const char*& it, const char* pEnd, boost::string_view& svResult)
{
    const char* pFirst = it;

    if (it + 7 > pEnd)
    {
        return EParserResult::UnexpectedEnd;
    }

    bool bOk = (*it++ == 'S');
    bOk = bOk && (*it++ == 'I');
    bOk = bOk && (*it++ == 'P');
    bOk = bOk && (*it++ == '/');
    bOk = bOk && std::isdigit(*it++);
    bOk = bOk && (*it++ == '.');
    bOk = bOk && std::isdigit(*it++);

    if (!bOk)
    {
        return EParserResult::BadVersion;
    }
    
    svResult = make_string(pFirst, it);

    return EParserResult::Success;
}

//! Parses a #ISIPRequest
EParserResult CSipParser::ParseRequest(const char* szData, size_t uSize, ISIPRequest& Request)
{
    const char* pEnd = szData + uSize;

    // Read the method from the message
    boost::string_view svMethod;
    EParserResult eStatus = ParseMethod(szData, pEnd, svMethod);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    // Attempt to convert the svMethod to enum
    const auto eMethod = GetSipMethodEnum(svMethod.to_string().c_str());

    if (ESipMethod::Unknown == eMethod)
    {
        eStatus = EParserResult::BadMethod;
        return eStatus;
    }

    // Read the target URI
    boost::string_view svTarget;
    eStatus = ParseTarget(szData, pEnd, svTarget);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    // Read the version string
    boost::string_view svVersion;
    eStatus = ParseVersion(szData, pEnd, svVersion);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    // Skip pFirst CRLF
    if (szData + 2 > pEnd)
    {
        eStatus = EParserResult::UnexpectedEnd;
        return eStatus;
    }

    if (szData[0] != '\r' || szData[1] != '\n')
    {
        eStatus = EParserResult::BadLineEnding;
        return eStatus;
    }
    szData += 2;

    // Copy parsed data
    Request.Method(eMethod);
    Request.URI(svTarget.to_string().c_str());
    Request.Version(svVersion.to_string().c_str());

    // Parse fields and content
    return ParseMessage(szData, pEnd, Request);
}

/* Response parsing */

EParserResult CSipParser::ParseResponse(const char* szData, size_t uSize, ISIPResponse& Response)
{
    return EParserResult::Success;
}