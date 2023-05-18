#ifndef _TCONTAINER_H_
#define _TCONTAINER_H_

#include "IContainer.h"
#include <vector>

//! @brief A base implementation of #IContainer
template<typename value_type, typename data_type>
class TContainer : public IContainer<value_type>, private IContainerIterator<value_type>
{
private:
    using vector_t = std::vector<data_type>;
    using iterator_t = typename vector_t::iterator;
    using const_iterator_t = typename vector_t::const_iterator;

    //! Stores the actual data
    mutable vector_t m_vector;

    //! Points to the item being iterated
    mutable iterator_t m_iter;

    //! @name Overrides from #IContainerIterator
    //! @{
    size_t index() const override
    {
        return std::distance<const_iterator_t>(m_vector.cbegin(), m_iter);
    }

    operator bool() const override
    {
        return (m_vector.cend() != m_iter);
    }

    void operator++() const override
    {
        ++m_iter;
    }

    value_type& operator*() override
    {
        return *m_iter;
    }

    value_type* operator->() override
    {
        return &(*m_iter);
    }

    const value_type& operator*() const override
    {
        return *m_iter;
    }

    const value_type* operator->() const override
    {
        return &(*m_iter);
    }
    //! @}

public:
    //! @name Overrides from #IContainer
    //! @{
    void clear() override
    {
        m_vector.clear();
    }

    void reserve(size_t count) override
    {
        m_vector.reserve(count);
    }

    value_type& emplace_back() override
    {
        m_vector.emplace_back();
        return m_vector.back();
    }

    value_type& emplace_front() override
    {
        auto it = m_vector.emplace(m_vector.begin());
        return *it;
    }

    value_type& insert(size_t index) override
    {
        auto it = m_vector.emplace(std::next(m_vector.begin(), index));
        return *it;
    }

    void pop_back() override
    {
        m_vector.pop_back();
    }

    void pop_front() override
    {
        m_vector.erase(m_vector.begin());
    }

    void erase(size_t index) override
    {
        m_vector.erase(std::next(m_vector.begin(), index));
    }

    value_type& at(size_t index) override
    {
        return m_vector.at(index);
    }

    value_type& operator[](size_t index) override
    {
        return at(index);
    }

    value_type& front() override
    {
        return m_vector.front();
    }

    value_type& back() override
    {
        return m_vector.back();
    }

    const value_type& at(size_t index) const override
    {
        return m_vector.at(index);
    }

    virtual const value_type& operator[](size_t index) const override
    {
        return at(index);
    }

    virtual const value_type& front() const override
    {
        return m_vector.front();
    }

    virtual const value_type& back() const override
    {
        return m_vector.back();
    }

    virtual size_t size() const override
    {
        return m_vector.size();
    }

    virtual bool empty() const override
    {
        return m_vector.empty();
    }

    virtual IContainerIterator& iterate() override
    {
        m_iter = m_vector.begin();
        return *this;
    }

    virtual const IContainerIterator& iterate() const
    {
        m_iter = m_vector.begin();
        return *this;
    }
    //! @}
};

template<typename value_type>
class TMemberAssigner
{
public:
    using fnAssign_t = void (value_type::*)(const value_type&);

    TMemberAssigner(fnAssign_t fn)
        : m_fnAssign(fn)
    {

    }

    void operator ()(const value_type& From, value_type& To) const
    {
        std::invoke(m_fnAssign, To, From);
    }

private:
    fnAssign_t m_fnAssign;
};

template<typename value_type, typename assigner_type = TMemberAssigner<value_type>>
void CopyContainer(const IContainer<value_type>& From, IContainer<value_type>& To, assigner_type Assigner)
{
    To.reserve(From.size());
    for (auto& it = From.iterate(); it; ++it)
        Assigner(*it, To.emplace_back());
}

#endif