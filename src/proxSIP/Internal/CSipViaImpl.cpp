#include "Internal/CSipViaImpl.h"

CSipViaImpl::CSipViaImpl()
{

}

/* Overrides from #ISipVia */

void CSipViaImpl::Assign(const ISipVia& Copy)
{
    Version(Copy.Version());
    Transport(Copy.Transport());
    URI(Copy.URI());
    TSIPFieldImpl::Assign(Copy);
}

const char* CSipViaImpl::Version() const
{
    return m_sVersion.c_str();
}

void CSipViaImpl::Version(const char* sVersion)
{
    m_sVersion = sVersion;
}

const char* CSipViaImpl::Transport() const
{
    return m_sTransport.c_str();
}

void CSipViaImpl::Transport(const char* sTransport)
{
    m_sTransport = sTransport;
}

const char* CSipViaImpl::URI() const
{
    return m_sURI.c_str();
}

void CSipViaImpl::URI(const char* sURI)
{
    m_sURI = sURI;
}

/* Overrides from #ISipField */

bool CSipViaImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pEnd = pData + uSize;
    
    // Check protocol
    // Currently only 2.0 is supported
    {
        
        // Use array instead of string to avoid storing the \0 terminator
        static const char arrProtocol[] = { 'S', 'I', 'P', '/', '2', '.', '0' };

        if (pData + sizeof(arrProtocol) > pEnd)
            return false; /* Unexpected end */

        if (0 != memcmp(pData, arrProtocol, sizeof(arrProtocol)))
            return false; /* Bad version */

        m_sVersion = std::string(arrProtocol, sizeof(arrProtocol));
        pData += sizeof(arrProtocol);
    }

    // Skip the /
    if (pData >= pEnd)
        return false; /* Unexpected end */

    if (*pData++ != '/')
        return false; /* Bad protocol */

    // Check transport
    // Currently only UDP is supported
    {
        static const char arrTransport[] = { 'U', 'D', 'P' };

        if (pData + sizeof(arrTransport) > pEnd)
            return false; /* Unexpected end */

        if (0 != memcmp(pData, arrTransport, sizeof(arrTransport)))
            return false; /* Bad version */

        m_sTransport = std::string(arrTransport, sizeof(arrTransport));
        pData += sizeof(arrTransport);
    }

    // Skip the SP
    if (pData >= pEnd)
        return false; /* Unexpected end */

    if (*pData++ != ' ')
        return false; /* Bad transport */

    // Read the URI until EOF or ;
    const char* pStartURI = pData;
    
    for (;;)
    {
        if (pData >= pEnd)
            break;

        if (*pData == ';')
            break;

        ++pData;
    }
    
    m_sURI = std::string(pStartURI, pData - pStartURI);

    // Parse the additional parameters
    return TSIPFieldImpl::Parse(pData, pEnd - pData);
}

void CSipViaImpl::Serialize(IOutputBuffer& Buffer) const
{
    const std::string sText
        = m_sVersion + "/" + m_sTransport + " " + m_sURI;

    Buffer.write(sText.data(), sText.size());

    // Write the additional parameters
    TSIPFieldImpl::Serialize(Buffer);
}