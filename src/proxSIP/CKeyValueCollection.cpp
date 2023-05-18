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

void CKeyValueCollection::Assign(const IKeyValueCollection& Copy)
{
    m_pImpl->Assign(Copy);
}

const char* CKeyValueCollection::Find(const char* szKey) const
{
    return m_pImpl->Find(szKey);
}

void CKeyValueCollection::Insert(const char* szKey, const char* szValue)
{
    return m_pImpl->Insert(szKey, szValue);
}

void CKeyValueCollection::clear()
{
    m_pImpl->clear();
}

bool CKeyValueCollection::empty() const
{
    return m_pImpl->empty();
}

size_t CKeyValueCollection::size() const
{
    return m_pImpl->size();
}

IContainerIterator<IKeyValuePair>& CKeyValueCollection::iterate()
{
    return m_pImpl->iterate();
}

const IContainerIterator<IKeyValuePair>& CKeyValueCollection::iterate() const
{
    return m_pImpl->iterate();
}