#ifndef _IKEYVALUECOLLECTION_H_
#define _IKEYVALUECOLLECTION_H_

#include "IKeyValuePair.h"

//! Iterates over the key-value collection
class PROXSIP_API IKeyValueEnumerator
{
public:
    virtual ~IKeyValueEnumerator() = default;

    //! Checks if the iterator points to a valid item in the collection
    virtual operator bool() const = 0;

    //! Increments the iterator to the next item
    virtual void operator++() const = 0;

    //! Mutator to the underlying pair
    virtual IKeyValuePair& operator*() = 0;

    //! Mutator to the underlying pair
    virtual IKeyValuePair* operator->() = 0;

    //! Accessor to the underlying pair
    virtual const IKeyValuePair& operator*() const = 0;

    //! Accessor to the underlying pair
    virtual const IKeyValuePair* operator->() const = 0;
};

//! A collection of key=value pairs
class PROXSIP_API IKeyValueCollection
{
public:
    virtual ~IKeyValueCollection() = default;

    //! Copies contents from another collection
    virtual void Assign(const IKeyValueCollection&) = 0;

    //! Finds the value corresponding to the requested key, if it exists
    //! @param[in] szKey The name of the key to find
    //! @return The found value, or nullptr if it does not exist
    virtual const char* Find(const char* szKey) const = 0;

    //! Sets the provided value and key in the collection (replaces if existing)
    //! @param[in] szKey The key
    //! @param[in] szValue The value
    virtual void Insert(const char* szKey, const char* szValue) = 0;

    //! Erases all items in the collection
    virtual void Clear() = 0;

    //! Checks if the collection is empty
    virtual bool Empty() const = 0;

    //! Reads the number of stored items
    virtual size_t Size() const = 0;

    //! Resets the enumerator to the start of the collection and returns a reference to it
    virtual IKeyValueEnumerator& StartEnumerator() = 0;

    //! Resets the enumerator to the start of the collection and returns a reference to it
    virtual const IKeyValueEnumerator& StartEnumerator() const = 0;
};

#endif