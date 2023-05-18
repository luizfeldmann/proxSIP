#include "Internal/CKeyValueCollectionImpl.h"

/* CKeyValueCollectionImpl */

CKeyValueCollectionImpl::CKeyValueCollectionImpl()
{

}

// Construct copy from abstract
CKeyValueCollectionImpl::CKeyValueCollectionImpl(const IKeyValueCollection& copy)
{
    for (auto& it = copy.iterate(); it; ++it)
    {
        m_map.get<tag_sequence>().emplace_back(pair_t{ it->Key(), it->Value() });
    }
}

CKeyValueCollectionImpl::CKeyValueCollectionImpl(const CKeyValueCollectionImpl&) = default;

CKeyValueCollectionImpl& CKeyValueCollectionImpl::operator=(const CKeyValueCollectionImpl&) = default;

CKeyValueCollectionImpl::CKeyValueCollectionImpl(CKeyValueCollectionImpl&&) noexcept = default;

CKeyValueCollectionImpl& CKeyValueCollectionImpl::operator=(CKeyValueCollectionImpl&&) noexcept = default;

/* Overrides from #IKeyValueEnumerator */

size_t CKeyValueCollectionImpl::index() const
{
    return std::distance(m_map.get<tag_sequence>().cbegin(), m_iter);
}

CKeyValueCollectionImpl::operator bool() const
{
    return (m_map.get<tag_sequence>().cend() != m_iter);
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
    m_map.get<tag_sequence>().modify(m_iter, [szValue](auto& item)
    {
        item.second = szValue;
    });
}

/* Overrides from #IKeyValueCollection */

void CKeyValueCollectionImpl::Assign(const IKeyValueCollection& Copy)
{
    clear();
    for (auto& it = Copy.iterate(); it; ++it)
        m_map.get<tag_sequence>().emplace_back(pair_t{ it->Key(), it->Value() });
}

const char* CKeyValueCollectionImpl::Find(const char* szKey) const
{
    const char* szValue = nullptr;

    auto itFind = m_map.get<tag_key>().find(szKey);

    if (m_map.get<tag_key>().cend() != itFind)
        szValue = itFind->second.c_str();

    return szValue;
}

void CKeyValueCollectionImpl::Insert(const char* szKey, const char* szValue)
{
    auto itFind = m_map.get<tag_key>().find(szKey);

    if (m_map.get<tag_key>().cend() != itFind)
    {
        m_map.get<tag_key>().modify(itFind, [szValue](auto& item)
            {
                item.second = szValue;
            });
    }
    else
    {
        m_map.get<tag_sequence>().emplace_back(pair_t{szKey, szValue});
    }
}

void CKeyValueCollectionImpl::clear()
{
    m_map.clear();
}

bool CKeyValueCollectionImpl::empty() const
{
    return m_map.empty();
}

size_t CKeyValueCollectionImpl::size() const
{
    return m_map.size();
}

IContainerIterator<IKeyValuePair>& CKeyValueCollectionImpl::iterate()
{
    m_iter = m_map.get<tag_sequence>().begin();
    return *this;
}

const IContainerIterator<IKeyValuePair>& CKeyValueCollectionImpl::iterate() const
{
    m_iter = m_map.get<tag_sequence>().begin();
    return *this;
}