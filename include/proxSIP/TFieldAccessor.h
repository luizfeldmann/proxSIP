#ifndef _TFIELDACCESSOR_H_
#define _TFIELDACCESSOR_H_

#include "ESipField.h"

//! Utility to read/write SIP fields to specialized objects
template<typename FieldT, typename CollectionT>
class TFieldAccessor
{
private:
    FieldT m_field;
    ESipField m_eField;
    CollectionT& m_collection;

    auto FieldName() const
    {
        return GetSipFieldStr(m_eField);
    }

public:
    TFieldAccessor(ESipField eField, CollectionT& Col)
        : m_eField(eField)
        , m_collection(Col)
    {

    }

    //! Updates the internal field object with the data read from the field collection
    bool Read()
    {
        bool bStatus = false;

        const char* sVal = m_collection.Find(FieldName());
        if (sVal)
        {
            bStatus = m_field.Parse(sVal, strlen(sVal));
        }

        return bStatus;
    }

    // Updates the field collection with the serialized data from the field object
    template<typename Buffer = TStrBuffer<std::string>>
    void Write()
    {
        Buffer buff;
        m_field.Serialize(buff);

        m_collection.Insert(FieldName(), buff.c_str());
    }

    //! Mutator to underlying object
    FieldT& operator*()
    {
        return m_field;
    }

    //! Accessor to underlying object
    const FieldT& operator*() const
    {
        return m_field;
    }

    //! Mutator to underlying object
    FieldT* operator->()
    {
        return &m_field;
    }

    //! Accessor to underlying object
    const FieldT& operator->() const
    {
        return &m_field;
    }
};

//! Constructs a #TFieldAccessor from the provided collection
template<typename FieldT, typename CollectionT>
auto CreateFieldAccessor(ESipField eField, CollectionT& Col)
{
    return TFieldAccessor<FieldT, CollectionT>(eField, Col);
}

#endif