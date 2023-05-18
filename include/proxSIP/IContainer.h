#ifndef _ICONTAINER_H_
#define _ICONTAINER_H_

#include "proxSIPExports.h"

//! Iterates the #IContainer
template <typename value_type>
class PROXSIP_API IContainerIterator
{
public:
    virtual ~IContainerIterator() = default;

    //! Gets the index of the current item in the collection
    virtual size_t index() const = 0;

    //! Checks if the iterator points to a valid item in the collection
    virtual operator bool() const = 0;

    //! Increments the iterator to the next item
    virtual void operator++() const = 0;

    //! Mutator to the underlying pair
    virtual value_type& operator*() = 0;

    //! Mutator to the underlying pair
    virtual value_type* operator->() = 0;

    //! Accessor to the underlying pair
    virtual const value_type& operator*() const = 0;

    //! Accessor to the underlying pair
    virtual const value_type* operator->() const = 0;
};

//! A generic container type
template <typename value_type>
class PROXSIP_API IContainer
{
public:
    virtual ~IContainer() = default;

    //! @brief Erases all the contained elements
    virtual void clear() = 0;

    //! @brief Pre-allocates space for the number of items
    virtual void reserve(size_t count) = 0;

    //! @brief Default-constructs an element in-place in the back of the container
    virtual value_type& emplace_back() = 0;

    //! @brief Default-constructs an element in-place in the front of the container
    virtual value_type& emplace_front() = 0;

    //! @brief Default-constructs an element in the requested position
    virtual value_type& insert(size_t) = 0;

    //! @brief Erases the last element
    virtual void pop_back() = 0;

    //! @brief Erases the first element
    virtual void pop_front() = 0;

    //! @brief Removes the element at a given index
    virtual void erase(size_t) = 0;

    //! @brief Gets a reference to the element at a certain index
    virtual value_type& at(size_t) = 0;

    //! @brief Gets a reference to the element at a certain index
    virtual value_type& operator[](size_t) = 0;

    //! @brief Gets a reference to the first element
    virtual value_type& front() = 0;

    //! @brief Gets a reference to the last element
    virtual value_type& back() = 0;

    //! @brief Gets a reference to the element at a certain index
    virtual const value_type& at(size_t) const = 0;

    //! @brief Gets a reference to the element at a certain index
    virtual const value_type& operator[](size_t) const = 0;

    //! @brief Gets a reference to the first element
    virtual const value_type& front() const = 0;

    //! @brief Gets a reference to the last element
    virtual const value_type& back() const = 0;

    //! @brief Gets the number of elements in the container
    virtual size_t size() const = 0;

    //! @brief Checks if the container is empty
    virtual bool empty() const = 0;

    //! @brief Starts iterating the collection
    virtual IContainerIterator<value_type>& iterate() = 0;
    
    //! @brief Starts iterating the collection
    virtual const IContainerIterator<value_type>& iterate() const = 0;
};

#endif