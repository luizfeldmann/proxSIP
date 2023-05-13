#ifndef _CSIPCONTACTIMPL_H_
#define _CSIPCONTACTIMPL_H_

#include "ISipContact.h"
#include "TSIPFieldImpl.h"
#include <string>

//! @copydoc ISipContact
class CSipContactImpl : public TSIPFieldImpl<ISipContact>
{
private:
    //! Stores the display name
    std::string m_sName;

    //! Stores the URI
    std::string m_sURI;

public:
    CSipContactImpl();

    //! @name Overrides from #ISipContact
    //! @{
    const char* Name() const override;

    void Name(const char*) override;

    const char* URI() const override;

    void URI(const char*) override;
    //! @}

    //! @name Overrides from #ISipField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IBuffer&) const override;
    //! @}
};

#endif