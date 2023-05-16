#include "CSipURI.h"
#include "Internal/CSipURIImpl.h"

CSipURI::CSipURI()
    : m_pImpl(new CSipURIImpl)
{

}

CSipURI::~CSipURI()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

ESipURIComponents CSipURI::QueryComponents() const
{
    return m_pImpl->QueryComponents();
}

void CSipURI::DropComponents(ESipURIComponents eComps)
{
    m_pImpl->DropComponents(eComps);
}

void CSipURI::KeepComponents(ESipURIComponents eComps)
{
    m_pImpl->KeepComponents(eComps);
}

const char* CSipURI::Protocol() const
{
    return m_pImpl->Protocol();
}

void CSipURI::Protocol(const char* sProto)
{
    m_pImpl->Protocol(sProto);
}

const char* CSipURI::User() const
{
    return m_pImpl->User();
}

void CSipURI::User(const char* sUser)
{
    m_pImpl->User(sUser);
}

const char* CSipURI::Password() const
{
    return m_pImpl->Password();
}

void CSipURI::Password(const char* sPassword)
{
    m_pImpl->Password(sPassword);
}

const char* CSipURI::Host() const
{
    return m_pImpl->Host();
}

void CSipURI::Host(const char* sHost)
{
    m_pImpl->Host(sHost);
}

unsigned short CSipURI::Port() const
{
    return m_pImpl->Port();
}

void CSipURI::Port(unsigned short usPort)
{
    m_pImpl->Port(usPort);
}

const IKeyValueCollection& CSipURI::Parameters() const
{
    return m_pImpl->Parameters();
}

IKeyValueCollection& CSipURI::Parameters()
{
    return m_pImpl->Parameters();
}

bool CSipURI::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSipURI::Serialize(IBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}