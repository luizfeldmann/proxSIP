#ifndef _CSIPURI_H_
#define _CSIPURI_H_

#include "ISipURI.h"

class CSipURIImpl;

//! Implementation of #ISipURI
//! @details @copybrief ISipURI
class PROXSIP_API CSipURI : public ISipURI
{
private:
    //! Pointer to internal implementation
    CSipURIImpl* m_pImpl;

public:
    CSipURI();
    ~CSipURI();

    //! @name Overrides from #ISipURI
    //! @{
    void Assign(const ISipURI&) override;

    ESipURIComponents QueryComponents() const override;

    void DropComponents(ESipURIComponents) override;

    void KeepComponents(ESipURIComponents) override;

    const char* Protocol() const override;

    void Protocol(const char*) override;

    const char* User() const override;

    void User(const char*) override;

    const char* Password() const override;

    void Password(const char*) override;

    const char* Host() const override;

    void Host(const char*) override;

    unsigned short Port() const override;

    void Port(unsigned short) override;

    const char* c_str() const override;
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