#include "CSipContact.h"
#include "Internal/CSipContactImpl.h"

CSipContact::CSipContact()
    : m_pImpl(new CSipContactImpl)
{

}

CSipContact::~CSipContact()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

/* Overrides from #ISipContact */

const char* CSipContact::Name() const
{
    return m_pImpl->Name();
}

void CSipContact::Name(const char* sName)
{
    m_pImpl->Name(sName);
}

const ISipURI& CSipContact::URI() const
{
    return m_pImpl->URI();
}

ISipURI& CSipContact::URI()
{
    return m_pImpl->URI();
}

//! @}

/* Overrides from #ISipField */

const IKeyValueCollection& CSipContact::Parameters() const
{
    return m_pImpl->Parameters();
}

IKeyValueCollection& CSipContact::Parameters()
{
    return m_pImpl->Parameters();
}

bool CSipContact::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSipContact::Serialize(IOutputBuffer& Buffer) const
{
    return m_pImpl->Serialize(Buffer);
}