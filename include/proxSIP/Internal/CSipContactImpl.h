#ifndef _CSIPCONTACTIMPL_H_
#define _CSIPCONTACTIMPL_H_

#include "ISipContact.h"
#include "TSIPFieldImpl.h"
#include "CSipURIImpl.h"
#include <string>

//! @copydoc ISipContact
class CSipContactImpl : public TSIPFieldImpl<ISipContact>
{
private:
    //! Stores the display name
    std::string m_sName;

    //! Stores the URI
    CSipURIImpl m_cURI;

public:
    CSipContactImpl();

    //! @name Overrides from #ISipContact
    //! @{
    const char* Name() const override;

    void Name(const char*) override;

    const ISipURI& URI() const override;

    ISipURI& URI() override;
    //! @}

    //! @name Overrides from #ISipField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif