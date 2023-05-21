#ifndef _CKEYVALUEPAIR_H_
#define _CKEYVALUEPAIR_H_

#include "IKeyValuePair.h"
#include "TImplPtr.h"

class CKeyValuePairImpl;
DECLARE_PIMPL(CKeyValuePairImpl);

//! Trivial implementation of IKeyValuePair
class PROXSIP_API CKeyValuePair : public TImplPtr<CKeyValuePair, CKeyValuePairImpl>, public IKeyValuePair
{
public:
    //! Constructs a pair with the given name and value
    CKeyValuePair(const char* sName = "", const char* sValue = "");

    //! Copies from an abstract #IKeyValuePair
    CKeyValuePair(const IKeyValuePair&);

    //! @name Overrides from #IKeyValuePair
    //! @{
    const char* Key() const override;

    void Key(const char*) override;

    const char* Value() const override;

    void Value(const char*) override;
    //! @}
};

#endif