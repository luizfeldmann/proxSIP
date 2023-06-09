#include "CSIPResponse.h"
#include "Internal/CSIPResponseImpl.h"

/* CSIPResponse */

CSIPResponse::~CSIPResponse()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CSIPResponse::CSIPResponse()
    : m_pImpl(new CSIPResponseImpl)
{

}

/* Overrides from IMessage */
bool CSIPResponse::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSIPResponse::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}

/* Overrides from ISIPResponse */

void CSIPResponse::Assign(const ISIPResponse& Copy)
{
    return m_pImpl->Assign(Copy);
}

ESipStatusCode CSIPResponse::Status() const
{
    return m_pImpl->Status();
}

void CSIPResponse::Status(ESipStatusCode eStatus)
{
    m_pImpl->Status(eStatus);
}

/* Overrides from ISIPMessage */

void CSIPResponse::Assign(const ISIPMessage& Src)
{
    static_cast<ISIPMessage*>(m_pImpl)->Assign(Src);
}

const ESIPMessageType CSIPResponse::Type() const
{
    return m_pImpl->Type();
}

const char* CSIPResponse::Version() const
{
    return m_pImpl->Version();
}

void CSIPResponse::Version(const char* sVersion)
{
    m_pImpl->Version(sVersion);
}

const IEndpoint& CSIPResponse::Source() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPResponse::Source()
{
    return m_pImpl->Source();
}

const IEndpoint& CSIPResponse::Destination() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPResponse::Destination()
{
    return m_pImpl->Source();
}

const IContainer<ISipVia>& CSIPResponse::Via() const
{
    return m_pImpl->Via();
}

IContainer<ISipVia>& CSIPResponse::Via()
{
    return m_pImpl->Via();
}

const ISipContact& CSIPResponse::From() const
{
    return m_pImpl->From();
}

ISipContact& CSIPResponse::From()
{
    return m_pImpl->From();
}

const ISipContact& CSIPResponse::To() const
{
    return m_pImpl->To();
}

ISipContact& CSIPResponse::To()
{
    return m_pImpl->To();
}

const char* CSIPResponse::CallID() const
{
    return m_pImpl->CallID();
}

void CSIPResponse::CallID(const char* sID)
{
    m_pImpl->CallID(sID);
}

const IContainer<ISipContact>& CSIPResponse::Contact() const
{
    return m_pImpl->Contact();
}

IContainer<ISipContact>& CSIPResponse::Contact()
{
    return m_pImpl->Contact();
}

const IKeyValueCollection& CSIPResponse::Fields() const
{
    return m_pImpl->Fields();
}

IKeyValueCollection& CSIPResponse::Fields()
{
    return m_pImpl->Fields();
}

const char* CSIPResponse::ContentType() const
{
    return m_pImpl->ContentType();
}

void CSIPResponse::ContentType(const char* sType)
{
    m_pImpl->ContentType(sType);
}

size_t CSIPResponse::ContentLength() const
{
    return m_pImpl->ContentLength();
}

void CSIPResponse::ContentLength(size_t uLen)
{
    m_pImpl->ContentLength(uLen);
}

const IBuffer& CSIPResponse::Content() const
{
    return m_pImpl->Content();
}

IBuffer& CSIPResponse::Content()
{
    return m_pImpl->Content();
}