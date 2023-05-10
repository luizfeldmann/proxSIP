#ifndef _IBUFFER_H_
#define _IBUFFER_H_

#include "proxSIPExports.h"

//! Stores arbitrary data
class PROXSIP_API IBuffer
{
public:
    virtual ~IBuffer() = default;

    //! Gets the size of the stored data
    virtual size_t size() const = 0;

    //! Grows or shrinks the buffer
    virtual void resize(size_t) = 0;

    //! Accessor to the first element of contained data
    virtual const char* cbegin() const = 0;

    //! Mutator to the first element of contained data
    virtual char* begin() = 0;

    //! Iterator to the end of the buffer
    virtual const char* cend() const = 0;

    //! Iterator to the end of the buffer
    virtual char* end() = 0;
};

#endif