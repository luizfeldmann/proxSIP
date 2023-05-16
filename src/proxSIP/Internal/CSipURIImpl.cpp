#include "Internal/CSipURIImpl.h"
#include <algorithm>

/* Util */

const char* get_or_null(const CSipURIImpl::opt_string& opt)
{
    const char* szValue = nullptr;

    if (opt.has_value())
        szValue = opt.get().c_str();

    return szValue;
}

/* CSipURIImpl */

CSipURIImpl::CSipURIImpl()
{

}

ESipURIComponents CSipURIImpl::QueryComponents() const
{
    ESipURIComponents eComps = ESipURIComponents::None;

    if (m_proto.has_value())
        eComps = eComps | ESipURIComponents::Protocol;

    if (m_user.has_value())
        eComps = eComps | ESipURIComponents::User;

    if (m_password.has_value())
        eComps = eComps | ESipURIComponents::Password;

    if (m_host.has_value())
        eComps = eComps | ESipURIComponents::Host;

    if (m_port.has_value())
        eComps = eComps | ESipURIComponents::Port;

    if (!Parameters().Empty())
        eComps = eComps | ESipURIComponents::Parameters;

    //if ()
    //    eComps = eComps | ESipURIComponents::Headers;

    return eComps;
}

void CSipURIImpl::DropComponents(ESipURIComponents eDrop)
{
    if (ESipURIComponents::None != (eDrop & ESipURIComponents::Protocol))
        m_proto.reset();

    if (ESipURIComponents::None != (eDrop & ESipURIComponents::User))
        m_user.reset();

    if (ESipURIComponents::None != (eDrop & ESipURIComponents::Password))
        m_password.reset();

    if (ESipURIComponents::None != (eDrop & ESipURIComponents::Host))
        m_host.reset();

    if (ESipURIComponents::None != (eDrop & ESipURIComponents::Port))
        m_port.reset();

    if (ESipURIComponents::None != (eDrop & ESipURIComponents::Parameters))
        Parameters().Clear();

    //if (ESipURIComponents::None != (eDrop & ESipURIComponents::Headers))
    //    .clear();
}

void CSipURIImpl::KeepComponents(ESipURIComponents eCompsKeep)
{
    ESipURIComponents eCompsDrop = ESipURIComponents::All & ~eCompsKeep;
    DropComponents(eCompsDrop);
}

const char* CSipURIImpl::Protocol() const
{
    return get_or_null(m_proto);
}

void CSipURIImpl::Protocol(const char* sProto)
{
    m_proto.emplace(sProto);
}

const char* CSipURIImpl::User() const
{
    return get_or_null(m_user);
}

void CSipURIImpl::User(const char* sUser)
{
    m_user.emplace(sUser);
}

const char* CSipURIImpl::Password() const
{
    return get_or_null(m_password);
}

void CSipURIImpl::Password(const char* sPassword)
{
    m_password.emplace(sPassword);
}

const char* CSipURIImpl::Host() const
{
    return get_or_null(m_host);
}

void CSipURIImpl::Host(const char* sHost)
{
    m_host.emplace(sHost);
}

unsigned short CSipURIImpl::Port() const
{
    unsigned short usPort = 5060;

    if (m_port.has_value())
        usPort = m_port.get();

    return usPort;
}

void CSipURIImpl::Port(unsigned short usPort)
{
    m_port.emplace(usPort);
}

/* Overrides from ISipField */

bool CSipURIImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pEnd = pData + uSize;
    
    if (!ParseProtocol(pData, pEnd))
        return false;

    // Tokenize the URI
    const char* pColonBeforeAt = nullptr;   // Separates user:pass or host:port
    const char* pAt = nullptr;              // Location of the @
    const char* pColonAfterAt = nullptr;    // Separates host:port
    const char* pParams = nullptr;          // the ;key=val section
    const char* pFirst = pData;
    
    for (;;)
    {
        if (pData >= pEnd)
        {
            break;
        }
        else if (*pData == '@')
        {
            pAt = pData;
        }
        else if (*pData == ':')
        {
            if (pAt)
                pColonAfterAt = pData;
            else
                pColonBeforeAt = pData;
        }
        else if (*pData == ';')
        {
            pParams = pData;
            break;
        }

        ++pData;
    }

    bool bStatus;

    // Read the fields if they exist
    // Pass only the relevant part to the internal parser
    if (!pParams)
    {
        bStatus = DoParse(pFirst, pColonBeforeAt, pAt, pColonAfterAt, pEnd);
    }
    else
    {
        bStatus = DoParse(pFirst, pColonBeforeAt, pAt, pColonAfterAt, pParams);
        bStatus = bStatus && TSIPFieldImpl::Parse(pParams, pEnd - pParams);
    }

    return bStatus;
}

void CSipURIImpl::Serialize(IBuffer& Buffer) const
{
    // Handle local parameters
    {
        std::string sText;

        if (m_proto.has_value())
            sText += m_proto.get() + ":";

        if (m_user.has_value())
            sText += m_user.get();

        if (m_password.has_value())
            sText += ":" + m_password.get();

        if (m_host.has_value())
        {
            if (m_user.has_value())
                sText += "@";
            
            sText += m_host.get();
        }

        if (m_port.has_value())
            sText += ":" + std::to_string(m_port.get());

        Buffer.write(sText.data(), sText.size());
    }

    // Handle the parameters
    TSIPFieldImpl::Serialize(Buffer);
}

/* Internal */

bool CSipURIImpl::ParseProtocol(const char*& pData, const char* const pEnd)
{
    const char* pStart = pData;

    // Mandatory start of the URI
    static const char c_arrProto[] = { 's', 'i', 'p' };

    if (pData + sizeof(c_arrProto) >= pEnd)
        return false; /* Unexpected end */

    if (0 != memcmp(pData, c_arrProto, sizeof(c_arrProto)))
        return false; /* Bad protocol */

    // skip the 'sip'
    pData += sizeof(c_arrProto);

    // skip the 's' in 'sips'
    if (*pData == 's')
    {
        ++pData;

        if (pData >= pEnd)
            return false; /* Unexpected end */
    }

    if (*pData != ':')
        return false; /* Bad protocol */

    m_proto.emplace(pStart, pData - pStart);

    pData++; // skip the ':'

    return true;
}

bool CSipURIImpl::ParseUserPass(const char* pFirst, const char* pSep, const char* pEnd)
{
    if (pSep)
    {
        auto pStart = pSep + 1;
        m_password.emplace(pStart, pEnd - pStart);
    }
    else
    {
        pSep = pEnd;
    }

    m_user.emplace(pFirst, pSep - pFirst);

    return true;
}

bool CSipURIImpl::ParseHostPort(const char* pFirst, const char* pSep, const char* pEnd)
{
    bool bStatus = true;

    if (pSep)
    {
        auto pStart = pSep + 1;

        try
        {
            auto Port = std::stoi(std::string(pStart, pEnd - pStart));
            m_port.emplace(Port);
        }
        catch (...) { bStatus = false; }
    }
    else
    {
        pSep = pEnd;
    }

    m_host.emplace(pFirst, pSep - pFirst);

    return bStatus;
}

bool CSipURIImpl::ParseHeuristic(const char* pFirst, const char* pColon, const char* pEnd)
{
    bool bIsHostAndPort = false;

    // Decide if user(:pass) or host(:port) case
    if (pColon)
    {
        // if there is a collon, we check the right side is digit-only and means a port number
        bIsHostAndPort = std::all_of(pColon+1, pEnd, std::isdigit);
    }
    else
    {
        // if no collon, we check for '.' meaning it's an IP4 or qualified domain
        bIsHostAndPort = std::any_of(pFirst, pEnd, [](char c) {return c == '.'; });
    }

    // Actual parsing
    bool bStatus;

    if (bIsHostAndPort)
    {
        bStatus = ParseHostPort(pFirst, pColon, pEnd);
    }
    else
    {
        bStatus = ParseUserPass(pFirst, pColon, pEnd);
    }

    return true;
}

bool CSipURIImpl::DoParse(const char* pFirst, const char* pColonBefore, const char* pAt, const char* pColonAfter, const char* pEnd)
{
    bool bStatus;

    // sip(s):  hostname   :   port
    // sip(s):  username   :   password   @   hostname  :  port
    //          ^ first    ^ colon before ^ at          ^ colon after

    if (pAt)
    {
        // The URI is split
        // Left of @ = user(:pass)
        bStatus = ParseUserPass(pFirst, pColonBefore, pAt);

        // Right of @ = host(:port)
        bStatus = bStatus & ParseHostPort(pAt+1, pColonAfter, pEnd);
    }
    else
    {
        // The URI is incomplete
        // It may be just the user part, or just the host part
        bStatus = ParseHeuristic(pFirst, pColonBefore, pEnd);
    }

    return bStatus;
}
