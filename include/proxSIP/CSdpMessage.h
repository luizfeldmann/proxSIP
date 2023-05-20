#ifndef _CSDPMESSAGE_H_
#define _CSDPMESSAGE_H_

#include "ISdpMessage.h"

class CSdpMessageImpl;

//! Base implementation of #ISdpMessage
class PROXSIP_API CSdpMessage : public ISdpMessage
{
private:
    //! Pointer to implementation
    CSdpMessageImpl* m_pImpl;

    CSdpMessage(const CSdpMessage&) = delete;
    CSdpMessage& operator=(const CSdpMessage&) = delete;

public:
    CSdpMessage();
    ~CSdpMessage();

    //! @name Overrides from ISdpMessage
    //! @{
    
    //! @}
    
    //! @name Overrides from IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif