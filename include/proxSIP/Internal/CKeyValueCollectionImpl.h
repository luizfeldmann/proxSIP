#ifndef _CKEYVALUECOLLECTIONIMPL_H_
#define _CKEYVALUECOLLECTIONIMPL_H_

#include "IKeyValueCollection.h"
#include <string>
#include <map>

class CKeyValueCollectionImpl : public IKeyValueCollection, private IKeyValueEnumerator, private IKeyValuePair
{
private:
    using map_t = std::map<std::string, std::string>;

    //! Stores the actual data
    mutable map_t m_map;

    //! Points the the current item
    mutable map_t::iterator m_iter;

    //! @name Overrides from #IKeyValueEnumerator
    //! @{    
    operator bool() const override;

    void operator++() const override;

    IKeyValuePair& operator*() override;

    IKeyValuePair* operator->() override;

    const IKeyValuePair& operator*() const override;

    const IKeyValuePair* operator->() const override;
    //! @}
    

    //! @name Overrides from #IKeyValuePair
    //! @{
    const char* Key() const override;

    const char* Value() const override;

    void Value(const char* szValue) override;
    //! @}
    
public:
    //! Empty constructor
    CKeyValueCollectionImpl();

    // Construct copy from abstract
    CKeyValueCollectionImpl(const IKeyValueCollection& copy);

    //! Copy-constructible
    CKeyValueCollectionImpl(const CKeyValueCollectionImpl&);

    //! Copy-assignable
    CKeyValueCollectionImpl& operator=(const CKeyValueCollectionImpl&);

    //! Move-constructible
    CKeyValueCollectionImpl(CKeyValueCollectionImpl&&) noexcept;

    //! Move-assignable
    CKeyValueCollectionImpl& operator=(CKeyValueCollectionImpl&&) noexcept;

    //! @name Overrides from #IKeyValueCollection
    //! @{
    const char* Find(const char* szKey) const override;

    void Insert(const char* szKey, const char* szValue) override;

    size_t Size() const override;

    IKeyValueEnumerator& StartEnumerator() override;

    const IKeyValueEnumerator& StartEnumerator() const override;
    //! @}
};

#endif