#ifndef _CSIPCONTACT_H_
#define _CSIPCONTACT_H_

#include "ISipContact.h"

class CSipContactImpl;

//! @copydoc ISipContact
class PROXSIP_API CSipContact : public ISipContact
{
private:
    CSipContactImpl* m_pImpl;

    CSipContact(const CSipContact&) = delete;
    CSipContact& operator=(const CSipContact&) = delete;

public:
    CSipContact();
    ~CSipContact();

    //! @name Overrides from #ISipContact
    //! @{
    const char* Name() const override;

    void Name(const char*) override;

    const ISipURI& URI() const override;

    ISipURI& URI() override;
    //! @}

    //! @name Overrides from #ISipField
    //! @{
    const IKeyValueCollection& Parameters() const override;

    IKeyValueCollection& Parameters() override;

    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif