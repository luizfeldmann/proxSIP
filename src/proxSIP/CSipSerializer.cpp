#include "CSipSerializer.h"
#include "ESipField.h"
#include <string>

const static char* c_szSpace = " ";
const static char* c_szCRLF = "\r\n";
const static char* c_szFieldSep = ": ";

/* Util */

static void SerializeCommonField(ESipField eType, const ISipField& Field, IOutputBuffer& Buffer)
{
    // Write the name of the field
    const char* sKey = SipGetFieldStr(eType);
    Buffer.write(sKey, strlen(sKey));

    // Write the delimiter
    static const char szDelim[] = { ':', ' ' };
    Buffer.write(szDelim, sizeof(szDelim));

    // Write the value
    Field.Serialize(Buffer);

    // Write the end of line
    static const char szCRLF[] = { '\r', '\n' };
    Buffer.write(szCRLF, sizeof(szCRLF));
}

static void SerializeCommonFields(const ISIPMessage& Request, IOutputBuffer& Buffer)
{
    for (auto& it = Request.Via().iterate(); it; ++it)
        SerializeCommonField(ESipField::Via, *it, Buffer);

    SerializeCommonField(ESipField::From, Request.From(), Buffer);
    SerializeCommonField(ESipField::To, Request.To(), Buffer);

    for (auto& it = Request.Contact().iterate(); it; ++it)
        SerializeCommonField(ESipField::Contact, *it, Buffer);
}

static void SerializeFields(const ISIPMessage& Message, IOutputBuffer& Buffer)
{
    std::string sFields;

    for (const auto& it = Message.Fields().StartEnumerator(); it; ++it)
    {
        // Write the key
        const char* sKey = it->Key();

        if (!sKey)
            continue;

        sFields += sKey;
        sFields += c_szFieldSep;

        // Write the value
        const char* sValue = it->Value();
        if (sValue)
            sFields += sValue;

        // New line
        sFields += c_szCRLF;
    }

    // Final CRLF before the body
    sFields += c_szCRLF;

    Buffer.write(sFields.data(), sFields.size());
}

static void SerializeContent(const ISIPMessage& Message, IOutputBuffer& Buffer)
{
    const auto& rContent = Message.Content();
    const char* pData = rContent.cbegin();
    const size_t uSize = rContent.size();
    
    if (pData && uSize)
    {
        Buffer.write(pData, uSize);
    }
}

/* CSipSerializer */

void CSipSerializer::SerializeMessage(const ISIPMessage& Message, IOutputBuffer& Buffer)
{
    const auto eType = Message.Type();

    if (ESIPMessageType::Request == eType)
        SerializeRequest(dynamic_cast<const ISIPRequest&>(Message), Buffer);
    else if (ESIPMessageType::Response == eType)
        SerializeResponse(dynamic_cast<const ISIPResponse&>(Message), Buffer);
    else
        throw;
}

void CSipSerializer::SerializeRequest(const ISIPRequest& Request, IOutputBuffer& Buffer)
{
    // Header
    {
        // Build the start-line 
        std::string sHeader = SipGetMethodStr(Request.Method());
        sHeader += c_szSpace;
        sHeader += Request.URI().c_str();
        sHeader += c_szSpace;
        sHeader += Request.Version();
        sHeader += c_szCRLF;

        // Write the start-line
        Buffer.write(sHeader.data(), sHeader.size());
    }

    // Fields and content
    SerializeCommonFields(Request, Buffer);
    SerializeFields(Request, Buffer);
    SerializeContent(Request, Buffer);
}

void CSipSerializer::SerializeResponse(const ISIPResponse& Response, IOutputBuffer& Buffer)
{
    // Header
    {
        // Build the start-line
        const auto eStatus = Response.Status();
        const char* sMsg = GetSipStatusCodeStr(eStatus);

        std::string sHeader = Response.Version();
        sHeader += c_szSpace;
        sHeader += std::to_string((unsigned int)eStatus);

        if (sMsg)
        {
            sHeader += c_szSpace;
            sHeader += sMsg;
        }

        sHeader += c_szCRLF;

        // Write the start-line
        Buffer.write(sHeader.data(), sHeader.size());
    }

    // Fields and content
    SerializeCommonFields(Response, Buffer);
    SerializeFields(Response, Buffer);
    SerializeContent(Response, Buffer);
}