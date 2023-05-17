#include "CSipParser.h"
#include "ESipField.h"
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

static EParserResult ParseToCRLF(const char*& p, const char* pEnd, const char*& pToken)
{
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

            // Save end of the token
            pToken = p;

            // Skip the CRLF
            p += 2;
            break;
        }

        ++p;
    }

    return EParserResult::Success;
}

//! Handles header fields with special storage or adds the generic ones to the collection
static EParserResult HandleField(const boost::string_view& svName, const boost::string_view& svValue, ISIPMessage& Message)
{
    bool bStatus = true;
    auto eField = SipGetFieldEnum(svName.to_string().c_str());

    switch (eField)
    {
    case ESipField::From:
        bStatus = Message.From().Parse(svValue.data(), svValue.size());
        break;

    case ESipField::To:
        bStatus = Message.To().Parse(svValue.data(), svValue.size());
        break;

    default:
        const auto sKey = svName.to_string();
        const auto sValue = svValue.to_string();
        Message.Fields().Insert(sKey.c_str(), sValue.c_str());
        break;
    }

    return bStatus ? EParserResult::Success : EParserResult::BadFieldData;
}

//! Parse *one* field
static EParserResult ParseField(const char*& p, const char* pEnd, ISIPMessage& Message)
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

    // Tokenize the value
    boost::string_view svValue;
    {
        pFirst = p; // First character of value
        const char* pToken = p; // Last character of value

        const EParserResult eStatus = ParseToCRLF(p, pEnd, pToken);

        if (EParserResult::Success != eStatus)
            return eStatus;

        svValue = make_string(pFirst, pToken);
    }

    // Push the field into the message struct or add to special field
    return HandleField(svName, svValue, Message);
}

//! Parses all the fields
static EParserResult ParseFields(const char*& szData, const char* last, ISIPMessage& Message)
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
        eResult = ParseField(szData, last, Message);

        if (EParserResult::Success != eResult)
            break;
    }

    return eResult;
}

//! Parse body content
static EParserResult ParseContent(const char*& szData, const char* pEnd, ISIPMessage& Message)
{
    if (pEnd > szData)
    {
        size_t uContentLength = pEnd - szData;
        Message.Content().write(szData, uContentLength);
    }
    szData = pEnd;

    return EParserResult::Success;
}

//! Parse fields and body
static EParserResult ParseMessage(const char*& szData, const char* pEnd, ISIPMessage& Message)
{
    EParserResult eStatus = ParseFields(szData, pEnd, Message);

    if (EParserResult::Success == eStatus)
        eStatus = ParseContent(szData, pEnd, Message);

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
    const auto eMethod = SipGetMethodEnum(svMethod.to_string().c_str());

    if (ESipMethod::Unknown == eMethod)
    {
        eStatus = EParserResult::BadMethod;
        return eStatus;
    }

    Request.Method(eMethod);

    // Read the target URI
    boost::string_view svTarget;
    eStatus = ParseTarget(szData, pEnd, svTarget);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    if (!Request.URI().Parse(svTarget.data(), svTarget.size()))
    {
        eStatus = EParserResult::BadTarget;
        return eStatus;
    }

    // Read the version string
    boost::string_view svVersion;
    eStatus = ParseVersion(szData, pEnd, svVersion);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    Request.Version(svVersion.to_string().c_str());

    // Skip first CRLF
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

    // Parse fields and content
    eStatus = ParseMessage(szData, pEnd, Request);

    return eStatus;
}

/* Response parsing */

//! Parses the 3-digit status code + SP
static EParserResult ParseStatusCode(const char*& it, const char* pEnd, unsigned short& usCode)
{
    // Assert length
    if (it + 4 > pEnd)
    {
        return EParserResult::UnexpectedEnd;
    }

    // Verify digits + SP
    if (!std::isdigit(it[0]) || !std::isdigit(it[1]) || !std::isdigit(it[2]) || (' ' != it[3]))
    {
        return EParserResult::BadStatus;
    }

    // Read digits chars and cast to number
    usCode = 100 * (*it++ - '0');
    usCode += 10 * (*it++ - '0');
    usCode +=  1 * (*it++ - '0');
    ++it; // skip SP

    return EParserResult::Success;
}

EParserResult CSipParser::ParseResponse(const char* szData, size_t uSize, ISIPResponse& Response)
{
    const char* pEnd = szData + uSize;

    // Read the version string
    boost::string_view svVersion;
    EParserResult eStatus = ParseVersion(szData, pEnd, svVersion);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    Response.Version(svVersion.to_string().c_str());

    // Skip the space
    if (szData + 1 > pEnd)
    {
        eStatus = EParserResult::UnexpectedEnd;
        return eStatus;
    }

    if (*szData++ != ' ')
    {
        eStatus = EParserResult::BadVersion;
        return eStatus;
    }

    // Read the status code
    unsigned short usCode;
    eStatus = ParseStatusCode(szData, pEnd, usCode);

    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    // Validate the status code
    ESipStatusCode eCode = SipValidadeStatusCode(usCode);

    if (ESipStatusCode::Unknown == eCode)
    {
        eStatus = EParserResult::BadStatus;
        return eStatus;
    }

    Response.Status(eCode);

    // Read status reason
    const char* pFirstReason = szData;
    const char* pEndReason = szData;

    eStatus = ParseToCRLF(szData, pEnd, pEndReason);
    if (EParserResult::Success != eStatus)
    {
        return eStatus;
    }

    // Parse fields and content
    eStatus = ParseMessage(szData, pEnd, Response);

    return eStatus;
}