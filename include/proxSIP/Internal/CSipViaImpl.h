#ifndef _CSIPVIAIMPL_H_
#define _CSIPVIAIMPL_H_

#include "ISipVia.h"
#include "TSIPFieldImpl.h"

//! @copydoc ISipVia
class CSipViaImpl : public TSIPFieldImpl<ISipVia>
{
private:
    std::string m_sVersion;
    std::string m_sTransport;
    std::string m_sURI;

public:
    CSipViaImpl();

    //! @name Overrides from #ISipVia
    //! @{
    const char* Version() const override;

    void Version(const char*) override;

    const char* Transport() const override;

    void Transport(const char*) override;

    const char* URI() const override;

    void URI(const char*) override;
    //! @}

    //! @name Overrides from #ISipField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif