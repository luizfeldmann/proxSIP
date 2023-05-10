#ifndef _TBUFFER_H_
#define _TBUFFER_H_

#include "IBuffer.h"

//! Wraps an STD container using the IBuffer interface
template <typename Container>
class TBuffer : public IBuffer
{
private:
    Container m_container;

public:
    TBuffer()
    {

    }

    size_t size() const override
    {
        return m_container.size();
    }

    void resize(size_t n) override
    {
        m_container.resize(n);
    }

    const char* cbegin() const
    {
        return m_container.data();
    }

    char* begin()
    {
        return m_container.data();
    }

    const char* cend() const
    {
        return m_container.data() + m_container.size();
    }

    char* end()
    {
        return m_container.data() + m_container.size();
    }
};

#endif