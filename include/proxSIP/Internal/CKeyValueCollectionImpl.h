#ifndef _CKEYVALUECOLLECTIONIMPL_H_
#define _CKEYVALUECOLLECTIONIMPL_H_

#include "IKeyValueCollection.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <map>

class CKeyValueCollectionImpl : public IKeyValueCollection, private IKeyValueEnumerator, private IKeyValuePair
{
private:
    //! Tag used to index the elements sequentially
    struct tag_sequence;

    //! Tage used to find the elements by key name
    struct tag_key;

    //! Key value pair type
    using pair_t = std::pair<std::string, std::string>;

    //! Type of multi indexed container with both ordered sequencing and hashed lookup
    using multi_t = boost::multi_index_container<
        pair_t,
        boost::multi_index::indexed_by<
            boost::multi_index::sequenced<boost::multi_index::tag<tag_sequence>>,
            boost::multi_index::hashed_unique<boost::multi_index::tag<tag_key>,
                boost::multi_index::member<pair_t, std::string, &pair_t::first>>>>;

    //! Stores the actual data
    mutable multi_t m_map;

    //! Points the the current item
    mutable multi_t::index<tag_sequence>::type::iterator m_iter;

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

    void Clear() override;

    bool Empty() const override;

    size_t Size() const override;

    IKeyValueEnumerator& StartEnumerator() override;

    const IKeyValueEnumerator& StartEnumerator() const override;
    //! @}
};

#endif