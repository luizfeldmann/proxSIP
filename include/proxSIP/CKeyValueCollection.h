#ifndef _CKEYVALUECOLLECTION_H_
#define _CKEYVALUECOLLECTION_H_

#include "IKeyValueCollection.h"
#include "TImplPtr.h"

class CKeyValueCollectionImpl;
DECLARE_PIMPL(CKeyValueCollectionImpl);

//! Trivial implementation of IKeyValueCollection
class PROXSIP_API CKeyValueCollection : public TImplPtr<CKeyValueCollection, CKeyValueCollectionImpl>, public IKeyValueCollection
{
public:
    //! Constructs an empty collection
    CKeyValueCollection();

    //! Constructs a copy from the data of an abstract #IKeyValueCollection
    CKeyValueCollection(const IKeyValueCollection&);

    //! @name Overrides from IKeyValueCollection
    //! @{
    void Assign(const IKeyValueCollection&) override;

    const char* Find(const char* szKey) const override;

    void Insert(const char* szKey, const char* szValue) override;

    void clear() override;

    bool empty() const override;

    size_t size() const override;

    IContainerIterator<IKeyValuePair>& iterate() override;

    const IContainerIterator<IKeyValuePair>& iterate() const override;
    //! @}
};

#endif