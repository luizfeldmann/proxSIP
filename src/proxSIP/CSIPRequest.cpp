#include "CSIPRequest.h"
#include "Internal/CSIPRequestImpl.h"

/* CSIPRequest */

CSIPRequest::~CSIPRequest()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CSIPRequest::CSIPRequest()
    : m_pImpl(new CSIPRequestImpl)
{

}

/* Overrides from IMessage */
bool CSIPRequest::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSIPRequest::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}

/* Overrides from ISIPMessage */

void CSIPRequest::Assign(const ISIPMessage& Src)
{
    static_cast<ISIPMessage*>(m_pImpl)->Assign(Src);
}

const ESIPMessageType CSIPRequest::Type() const
{
    return m_pImpl->Type();
}

const char* CSIPRequest::Version() const
{
    return m_pImpl->Version();
}

void CSIPRequest::Version(const char* szVersion)
{
    m_pImpl->Version(szVersion);
}

const IEndpoint& CSIPRequest::Source() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPRequest::Source()
{
    return m_pImpl->Source();
}

const IEndpoint& CSIPRequest::Destination() const
{
    return m_pImpl->Destination();
}

IEndpoint& CSIPRequest::Destination()
{
    return m_pImpl->Destination();
}

const IContainer<ISipVia>& CSIPRequest::Via() const
{
    return m_pImpl->Via();
}

IContainer<ISipVia>& CSIPRequest::Via()
{
    return m_pImpl->Via();
}

const ISipContact& CSIPRequest::From() const
{
    return m_pImpl->From();
}

ISipContact& CSIPRequest::From()
{
    return m_pImpl->From();
}

const ISipContact& CSIPRequest::To() const
{
    return m_pImpl->To();
}

ISipContact& CSIPRequest::To()
{
    return m_pImpl->To();
}

const char* CSIPRequest::CallID() const
{
    return m_pImpl->CallID();
}

void CSIPRequest::CallID(const char* sID)
{
    m_pImpl->CallID(sID);
}

const IContainer<ISipContact>& CSIPRequest::Contact() const
{
    return m_pImpl->Contact();
}

IContainer<ISipContact>& CSIPRequest::Contact()
{
    return m_pImpl->Contact();
}

const IKeyValueCollection& CSIPRequest::Fields() const
{
    return m_pImpl->Fields();
}

IKeyValueCollection& CSIPRequest::Fields()
{
    return m_pImpl->Fields();
}

const char* CSIPRequest::ContentType() const
{
    return m_pImpl->ContentType();
}

void CSIPRequest::ContentType(const char* sType)
{
    m_pImpl->ContentType(sType);
}

size_t CSIPRequest::ContentLength() const
{
    return m_pImpl->ContentLength();
}

void CSIPRequest::ContentLength(size_t uLen)
{
    m_pImpl->ContentLength(uLen);
}

const IBuffer& CSIPRequest::Content() const
{
    return m_pImpl->Content();
}

IBuffer& CSIPRequest::Content()
{
    return m_pImpl->Content();
}

/* Overrides from ISIPRequest */

void CSIPRequest::Assign(const ISIPRequest& Copy)
{
    return m_pImpl->Assign(Copy);
}

ESipMethod CSIPRequest::Method() const
{
    return m_pImpl->Method();
}

void CSIPRequest::Method(ESipMethod eMethod)
{
    m_pImpl->Method(eMethod);
}

const ISipURI& CSIPRequest::URI() const
{
    return m_pImpl->URI();
}

ISipURI& CSIPRequest::URI()
{
    return m_pImpl->URI();
}