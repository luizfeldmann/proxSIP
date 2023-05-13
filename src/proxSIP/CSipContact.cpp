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

const char* CSipContact::URI() const
{
    return m_pImpl->URI();
}

void CSipContact::URI(const char* sUri)
{
    m_pImpl->URI(sUri);
}

//! @}

/* Overrides from #ISipField */

bool CSipContact::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSipContact::Serialize(IBuffer& Buffer) const
{
    return m_pImpl->Serialize(Buffer);
}