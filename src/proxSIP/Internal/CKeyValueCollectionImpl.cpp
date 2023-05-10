#include "Internal/CKeyValueCollectionImpl.h"

/* CKeyValueCollectionImpl */

CKeyValueCollectionImpl::CKeyValueCollectionImpl()
{

}

// Construct copy from abstract
CKeyValueCollectionImpl::CKeyValueCollectionImpl(const IKeyValueCollection& copy)
{
    for (auto& it = copy.StartEnumerator(); it; ++it)
    {
        m_map[it->Key()] = it->Value();
    }
}

CKeyValueCollectionImpl::CKeyValueCollectionImpl(const CKeyValueCollectionImpl&) = default;

CKeyValueCollectionImpl& CKeyValueCollectionImpl::operator=(const CKeyValueCollectionImpl&) = default;

CKeyValueCollectionImpl::CKeyValueCollectionImpl(CKeyValueCollectionImpl&&) noexcept = default;

CKeyValueCollectionImpl& CKeyValueCollectionImpl::operator=(CKeyValueCollectionImpl&&) noexcept = default;

/* Overrides from #IKeyValueEnumerator */

CKeyValueCollectionImpl::operator bool() const
{
    return (m_map.cend() != m_iter);
}

void CKeyValueCollectionImpl::operator++() const
{
    m_iter++;
}

IKeyValuePair& CKeyValueCollectionImpl::operator*()
{
    return *this;
}

IKeyValuePair* CKeyValueCollectionImpl::operator->()
{
    return this;
}

const IKeyValuePair& CKeyValueCollectionImpl::operator*() const
{
    return *this;
}

const IKeyValuePair* CKeyValueCollectionImpl::operator->() const
{
    return this;
}

/* Overrides from #IKeyValuePair */

const char* CKeyValueCollectionImpl::Key() const
{
    return m_iter->first.c_str();
}

const char* CKeyValueCollectionImpl::Value() const
{
    return m_iter->second.c_str();
}

void CKeyValueCollectionImpl::Value(const char* szValue)
{
    m_iter->second = szValue;
}

/* Overrides from #IKeyValueCollection */

const char* CKeyValueCollectionImpl::Find(const char* szKey) const
{
    const char* szValue = nullptr;

    auto itFind = m_map.find(szKey);

    if (m_map.cend() != itFind)
        szValue = itFind->second.c_str();

    return szValue;
}

void CKeyValueCollectionImpl::Insert(const char* szKey, const char* szValue)
{
    m_map[szKey] = szValue;
}

size_t CKeyValueCollectionImpl::Size() const
{
    return m_map.size();
}

IKeyValueEnumerator& CKeyValueCollectionImpl::StartEnumerator()
{
    m_iter = m_map.begin();
    return *this;
}

const IKeyValueEnumerator& CKeyValueCollectionImpl::StartEnumerator() const
{
    m_iter = m_map.begin();
    return *this;
}