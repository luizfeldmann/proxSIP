#include "CKeyValueCollection.h"
#include <string>
#include <map>

/* CKeyValueCollectionImpl */

class CKeyValueCollectionImpl : public IKeyValueEnumerator, public IKeyValuePair
{
public:
    using map_t = std::map<std::string, std::string>;
    map_t m_map;
    mutable map_t::iterator m_iter;

    //! Copy-constructible
    CKeyValueCollectionImpl(const CKeyValueCollectionImpl&) = default;

    //! Copy-assignable
    CKeyValueCollectionImpl& operator=(const CKeyValueCollectionImpl&) = default;

    //! Empty constructor
    CKeyValueCollectionImpl()
    {

    }

    // Construct copy from abstract
    CKeyValueCollectionImpl(const IKeyValueCollection& copy)
    {
        for (auto& it = copy.StartEnumerator(); it; ++it)
        {
            m_map[it->Key()] = it->Value();
        }
    }

    //! @name Overrides from IKeyValueEnumerator
    //! @{    
    operator bool() const override
    {
        return (m_map.cend() != m_iter);
    }

    void operator++() const override
    {
        m_iter++;
    }

    virtual IKeyValuePair& operator*() override
    {
        return *this;
    }

    virtual IKeyValuePair* operator->() override
    {
        return this;
    }

    //! Accessor to the underlying pair
    virtual const IKeyValuePair& operator*() const override
    {
        return *this;
    }

    virtual const IKeyValuePair* operator->() const override
    {
        return this;
    }

    //! @}
    
    //! @name Overrides from IKeyValuePair
    //! @{
    const char* Key() const override
    {
        return m_iter->first.c_str();
    }

    const char* Value() const override
    {
        return m_iter->second.c_str();
    }

    void Value(const char* szValue) override
    {
        m_iter->second = szValue;
    }
    //! @}
};

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
    const char* szValue = nullptr;

    auto itFind = m_pImpl->m_map.find(szKey);

    if (m_pImpl->m_map.cend() != itFind)
        szValue = itFind->second.c_str();

    return szValue;
}

void CKeyValueCollection::Insert(const char* szKey, const char* szValue)
{
    m_pImpl->m_map[szKey] = szValue;
}

size_t CKeyValueCollection::Size() const
{
    return m_pImpl->m_map.size();
}

IKeyValueEnumerator& CKeyValueCollection::StartEnumerator()
{
    m_pImpl->m_iter = m_pImpl->m_map.begin();
    return *m_pImpl;
}

const IKeyValueEnumerator& CKeyValueCollection::StartEnumerator() const
{
    m_pImpl->m_iter = m_pImpl->m_map.begin();
    return *m_pImpl;
}