#ifndef _TBUFFER_H_
#define _TBUFFER_H_

#include "IBuffer.h"

//! Wraps an STD container using the IBuffer interface
template <typename Container>
class TBuffer : public IBuffer
{
protected:
    //! Underlying container
    Container m_container;

public:
    TBuffer()
    {

    }

    void clear() override
    {
        m_container.clear();
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

    const char* cend() const
    {
        return m_container.data() + m_container.size();
    }

    void write(const char* pData, size_t uCount) override
    {
        m_container.insert(m_container.end(), pData, pData + uCount);
    }
};

//! Subtype of #TBuffer wrapping a container which can provide c_str()
template<typename Container>
class TStrBuffer : public TBuffer<Container>
{
public:
    //! Gets a null-terminate C-string from the buffer data
    const char* c_str() const
    {
        return m_container.c_str();
    }
};

#endif