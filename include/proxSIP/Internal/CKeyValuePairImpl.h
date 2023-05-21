#ifndef _CKEYVALUEPAIRIMPL_H_
#define _CKEYVALUEPAIRIMPL_H_

#include "IKeyValuePair.h"
#include <string>

//! Internal implementation of #IKeyValuePair
class CKeyValuePairImpl : public IKeyValuePair
{
protected:
    //! Stores the key
    std::string m_sKey;

    //! Stores the value
    std::string m_sValue;

public:
    //! Constructs using provided key and value
    CKeyValuePairImpl(const char* sKey = "", const char* sValue = "");

    //! Copies from abstract interface
    CKeyValuePairImpl(const IKeyValuePair&);

    //! Copy-construct
    CKeyValuePairImpl(const CKeyValuePairImpl&);

    //! Copy-assign
    CKeyValuePairImpl& operator=(const CKeyValuePairImpl&);

    //! Move-construct
    CKeyValuePairImpl(CKeyValuePairImpl&&) noexcept;

    // Move-assign
    CKeyValuePairImpl& operator=(CKeyValuePairImpl&&) noexcept;

    //! @name Overrides from #IKeyValuePair
    //! @{
    const char* Key() const override;

    void Key(const char *) override;

    const char* Value() const override;

    void Value(const char*) override;
    //! @}
};

#endif