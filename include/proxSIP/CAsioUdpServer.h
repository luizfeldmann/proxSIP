#ifndef _CASIOUDPSERVER_H_
#define _CASIOUDPSERVER_H_

#include "IUdpServer.h"

class CAsioUdpServerImpl;

//! Implements a UDP server using boost::asio
class PROXSIP_API CAsioUdpServer : public IUdpServer
{
private:
    //! Pointer to implementation
    CAsioUdpServerImpl* m_pImpl;

    CAsioUdpServer(const CAsioUdpServer&) = delete;
    CAsioUdpServer& operator=(const CAsioUdpServer&) = delete;

public:
    CAsioUdpServer();
    ~CAsioUdpServer();

    //! @name Overrides from IUdpMessageSender
    //! @{
    void SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst) override;
    //! @}
    
    //! @name Overrides from IUdpHttpServer
    //! @{
    IEndpoint& LocalEndpoint();
    const IEndpoint& LocalEndpoint() const;
    void SetHandler(IUdpMessageHandler*) override;
    bool Start() override;
    bool Stop() override;
    void Poll() override;
    // @}
};

#endif