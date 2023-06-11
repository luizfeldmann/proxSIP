#ifndef _IOUTPUTBUFFER_H_
#define _IOUTPUTBUFFER_H_

#include "proxSIPExports.h"
#include <cstddef>

//! Allows writing data into some buffer
class PROXSIP_API IOutputBuffer
{
public:
    virtual ~IOutputBuffer() = default;

    //! Copies data to inside the buffer
    virtual void write(const char*, size_t) = 0;
};

#endif