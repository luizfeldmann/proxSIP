#ifndef _IKEYVALUECOLLECTION_H_
#define _IKEYVALUECOLLECTION_H_

#include "IKeyValuePair.h"
#include "IContainer.h"

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
    virtual void clear() = 0;

    //! Checks if the collection is empty
    virtual bool empty() const = 0;

    //! Reads the number of stored items
    virtual size_t size() const = 0;

    //! Resets the enumerator to the start of the collection and returns a reference to it
    virtual IContainerIterator<IKeyValuePair>& iterate() = 0;

    //! Resets the enumerator to the start of the collection and returns a reference to it
    virtual const IContainerIterator<IKeyValuePair>& iterate() const = 0;
};

#endif