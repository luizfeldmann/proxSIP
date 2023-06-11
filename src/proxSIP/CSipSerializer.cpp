#include "CSipSerializer.h"
#include "ESipField.h"
#include <string>
#include <cstring>

static const char c_cSpace = ' ';
static const char arrCRLF[] = { '\r', '\n' };
static const char arrDelim[] = { ':', ' ' };

/* Util */

static void SerializeCommonField(ESipField eType, const char* sValue, size_t uValSize, IOutputBuffer& Buffer)
{
    // Write the name of the field
    const char* sKey = SipGetFieldStr(eType);
    Buffer.write(sKey, strlen(sKey));

    // Write the delimiter
    Buffer.write(arrDelim, sizeof(arrDelim));

    // Write the value
    Buffer.write(sValue, uValSize);

    // Write the end of line
    Buffer.write(arrCRLF, sizeof(arrCRLF));
}

static void SerializeCommonField(ESipField eType, const ISipField& Field, IOutputBuffer& Buffer)
{
    // Write the name of the field
    const char* sKey = SipGetFieldStr(eType);
    Buffer.write(sKey, strlen(sKey));

    // Write the delimiter
    Buffer.write(arrDelim, sizeof(arrDelim));

    // Write the value
    Field.Serialize(Buffer);

    // Write the end of line
    Buffer.write(arrCRLF, sizeof(arrCRLF));
}

static void SerializeCommonFields(const ISIPMessage& Message, IOutputBuffer& Buffer)
{
    // Vias
    for (auto& it = Message.Via().iterate(); it; ++it)
        SerializeCommonField(ESipField::Via, *it, Buffer);

    // From / To
    SerializeCommonField(ESipField::From, Message.From(), Buffer);
    SerializeCommonField(ESipField::To, Message.To(), Buffer);

    // Call-ID
    std::string sCallID = Message.CallID();
    SerializeCommonField(ESipField::CallID, sCallID.data(), sCallID.size(), Buffer);

    // Contacts
    for (auto& it = Message.Contact().iterate(); it; ++it)
        SerializeCommonField(ESipField::Contact, *it, Buffer);

    // Content-Length
    std::string sContentLength = std::to_string(Message.ContentLength());
    SerializeCommonField(ESipField::ContentLength, sContentLength.data(), sContentLength.size(), Buffer);

    // Content-Type
    const char* sContentType = Message.ContentType();
    if (sContentType && sContentType[0] != '\0')
        SerializeCommonField(ESipField::ContentType, sContentType, strlen(sContentType), Buffer);
}

static void SerializeFields(const ISIPMessage& Message, IOutputBuffer& Buffer)
{
    std::string sFields;

    for (const auto& it = Message.Fields().iterate(); it; ++it)
    {
        // Write the key
        const char* sKey = it->Key();

        if (!sKey)
            continue;

        sFields.append(sKey);
        sFields.append(arrDelim, sizeof(arrDelim));

        // Write the value
        const char* sValue = it->Value();
        if (sValue)
            sFields.append(sValue);

        // New line
        sFields.append(arrCRLF, sizeof(arrCRLF));
    }

    // Final CRLF before the body
    sFields.append(arrCRLF, sizeof(arrCRLF));

    // Push into buffer
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
        sHeader.append(1, c_cSpace);
        sHeader.append(Request.URI().c_str());
        sHeader.append(1, c_cSpace);
        sHeader.append(Request.Version());
        sHeader.append(arrCRLF, sizeof(arrCRLF));

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
        sHeader.append(1, c_cSpace);
        sHeader.append(std::to_string((unsigned int)eStatus));

        if (sMsg)
        {
            sHeader.append(1, c_cSpace);
            sHeader.append(sMsg);
        }

        sHeader.append(arrCRLF, sizeof(arrCRLF));

        // Write the start-line
        Buffer.write(sHeader.data(), sHeader.size());
    }

    // Fields and content
    SerializeCommonFields(Response, Buffer);
    SerializeFields(Response, Buffer);
    SerializeContent(Response, Buffer);
}