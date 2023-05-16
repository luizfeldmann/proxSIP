#ifndef _IBUFFER_H_
#define _IBUFFER_H_

#include "IOutputBuffer.h"

//! Stores arbitrary data
class PROXSIP_API IBuffer : public IOutputBuffer
{
public:
    virtual ~IBuffer() = default;

    //! Erases all the content
    virtual void clear() = 0;

    //! Gets the size of the stored data
    virtual size_t size() const = 0;

    //! Grows or shrinks the buffer
    virtual void resize(size_t) = 0;

    //! Accessor to the first element of contained data
    virtual const char* cbegin() const = 0;

    //! Iterator to the end of the buffer
    virtual const char* cend() const = 0;
};

#endif