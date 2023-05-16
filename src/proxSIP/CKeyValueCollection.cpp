#include "CKeyValueCollection.h"
#include "Internal/CKeyValueCollectionImpl.h"

/* CKeyValueCollectionImpl */

IMPLEMENT_PIMPL(CKeyValueCollectionImpl);

/* CKeyValueCollection */

CKeyValueCollection::CKeyValueCollection()
    : TImplPtr(new CKeyValueCollectionImpl)
{

}

CKeyValueCollection::CKeyValueCollection(const IKeyValueCollection& copy)
    : TImplPtr(new CKeyValueCollectionImpl(copy))
{

}

const char* CKeyValueCollection::Find(const char* szKey) const
{
    return m_pImpl->Find(szKey);
}

void CKeyValueCollection::Insert(const char* szKey, const char* szValue)
{
    return m_pImpl->Insert(szKey, szValue);
}

void CKeyValueCollection::Clear()
{
    m_pImpl->Clear();
}

bool CKeyValueCollection::Empty() const
{
    return m_pImpl->Empty();
}

size_t CKeyValueCollection::Size() const
{
    return m_pImpl->Size();
}

IKeyValueEnumerator& CKeyValueCollection::StartEnumerator()
{
    return m_pImpl->StartEnumerator();
}

const IKeyValueEnumerator& CKeyValueCollection::StartEnumerator() const
{
    return m_pImpl->StartEnumerator();
}