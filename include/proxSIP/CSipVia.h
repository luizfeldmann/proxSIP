#ifndef _CSIPVIA_H_
#define _CSIPVIA_H_

#include "ISipVia.h"

class CSipViaImpl;

//! @copydoc ISipVia
class PROXSIP_API CSipVia : public ISipVia
{
private:
    CSipViaImpl* m_pImpl;

    CSipVia(const CSipVia&) = delete;
    CSipVia& operator=(const CSipVia&) = delete;

public:
    CSipVia();
    ~CSipVia();

    //! @name Overrides from #ISipVia
    //! @{
    void Assign(const ISipVia&) override;

    const char* Version() const override;

    void Version(const char*) override;

    const char* Transport() const override;

    void Transport(const char*) override;

    const char* URI() const override;

    void URI(const char*) override;
    //! @}

    //! @name Overrides from #ISipField
    //! @{
    void Assign(const ISipField&) override;

    const IKeyValueCollection& Parameters() const override;

    IKeyValueCollection& Parameters() override;

    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @} 
};

#endif