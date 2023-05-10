#ifndef _TIMPLPTR_H_
#define _TIMPLPTR_H_

namespace ImplPtr
{
    //! Destroys the implementation object
    template <typename ImplT> void destroy(ImplT*);

    //! Clones the implementation object
    template <typename ImplT> ImplT* clone(const ImplT&);

    //! Copy-assigns the implementation object
    template <typename ImplT> void assign(ImplT& lhs, const ImplT& rhs);
}

//! Declares auxiliary templates for the implementation type
#define DECLARE_PIMPL(ImplT) \
namespace ImplPtr \
{ \
    template<> void destroy<ImplT>(ImplT*); \
    template<> ImplT* clone(const ImplT&); \
    template<> void assign(ImplT& lhs, const ImplT& rhs); \
}

//! Implements the auxiliary templates for the implementation type
#define IMPLEMENT_PIMPL(ImplT) \
namespace ImplPtr \
{ \
    template<> void destroy<ImplT>(ImplT* p) {delete p;} \
    template<> ImplT* clone(const ImplT& r) { return new ImplT(r);  } \
    template<> void assign(ImplT& lhs, const ImplT& rhs) { lhs = ImplT(rhs); } \
}

//! Base for a copyable, movable class with the 'pointer to implementation' design pattern
//! @tparam T The class with the private implementation pointer
//! @tparam ImplT The type of the implementation class
//!               The implementation object must be copy-constructible and copy-assignable
template <typename T, typename ImplT>
class TImplPtr
{
private:
	// Pointer to private implementation
	ImplT* m_pImpl;
	friend T;

public:
    ~TImplPtr()
	{
        ImplPtr::destroy<ImplT>(m_pImpl);
		m_pImpl = nullptr;
	}

    //! Constructs by receiving the implementation pointer
    TImplPtr(ImplT* pImpl)
        : m_pImpl(pImpl)
    {

    }

    //! Copy-constructor
    TImplPtr(const TImplPtr& copy)
        : m_pImpl(ImplPtr::clone<ImplT>(*copy.m_pImpl))
    {
        
    }

    //! Copy-assignment operator
    TImplPtr& operator=(const TImplPtr& copy)
    {
        ImplPtr::assign<ImplT>(*m_pImpl, *copy.m_pImpl);
        return *this;
    }

    //! Move-constructor
    TImplPtr(TImplPtr&& move) noexcept
        : m_pImpl(move.m_pImpl)
    {
        move.m_pImpl = nullptr;
    }

    //! Move-assignment operator
    TImplPtr& operator=(TImplPtr&& move) noexcept
    {
        ImplT* pMy = m_pImpl;
        m_pImpl = move.m_pImpl;
        move.m_pImpl = pMy;

        return *this;
    }
};

#endif