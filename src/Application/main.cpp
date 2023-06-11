#include <proxSIP/CAsioUdpServer.h>
#include <proxSIP/CSipMessageHandler.h>
#include <proxSIP/CSipServer.h>
#include <proxSIP/CAuthValidator.h>
#include <proxSIP/CSipRegistry.h>
#include "CCallSniffer.h"
#include "CRemoteSwitch.h"
#include "CAppConfig.h"
#include <iostream>
#include "version.h"

#ifdef _WIN32
// In windows we can use kbhit() to exit the loop
#include <conio.h>
#else
// In Linux we'll use signals
#include <signal.h>

volatile bool g_bTerminate = false;

static void OnSignal(sig_atomic_t)
{
    g_bTerminate = true;
}

#endif

int main(int argc, char** argv)
{
#ifndef _WIN32
    // Attach signals to use as stop condition
    signal(SIGINT, OnSignal);
    signal(SIGTERM, OnSignal);
#endif

    // Print the header text
    std::cout << APPLICATION_NAME << " [v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "." << VERSION_TWEAK << "]" << std::endl;

    // Read configutation
    const char* szConfigPath = nullptr;

    if (argc == 2)
        szConfigPath = argv[1];

    CAppConfig config(szConfigPath);

    // Create controller for remote switch gate
    CRemoteSwitch cSwitch;
    {
        std::string sUser, sPass;
        config.GetSwitchCredentials(sUser, sPass);
        cSwitch.SetAuth(sUser, sPass);

        std::string sHost, sTarget;
        unsigned short usPort = 80;

        config.GetSwitchEndpoint(sHost, usPort, sTarget);
        cSwitch.SetTarget(sTarget);
        cSwitch.Connect(sHost, usPort);
    }

    // Create handler for DTMF events
    class CGateOperator : IEvtHandlerDTMF
    {
    private:
        CRemoteSwitch& m_rGate;
        std::chrono::system_clock::time_point m_lastActivation = std::chrono::system_clock::time_point::min();
        std::chrono::system_clock::duration m_timeout;

    public:
        CGateOperator(CRemoteSwitch& rGate, std::chrono::system_clock::duration Interval)
            : m_rGate(rGate)
            , m_timeout(Interval)
        {

        }

        void OnEvent(const IRtpPhoneEvent& Evt) override
        {
            // Handle only the # key
            if (Evt.EventCode() != EPhoneEventCode::Pound)
                return;

            // Insert some time in between activations
            const auto now = std::chrono::system_clock::now();
            if (now < m_lastActivation + m_timeout)
                return;

            // Open the gate
            m_lastActivation = now;
            m_rGate.Activate();
        }
    } dtmfHandler(cSwitch, std::chrono::seconds(config.GetSwitchInterval()));

    // Create the server logic
    CSipServer sipServer;

    // Create registry for contacts
    CSipRegistry cRegistry;
    sipServer.SetRegistry(&cRegistry);

    // Create auth manager
    CAuthValidator cAuth;
    cAuth.SetAccounts(config.GetUsers());
    sipServer.SetAuth(&cAuth);

    // Create a sniffer to intercept the call
    CCallSniffer cSniffer;
    cSniffer.SetHandler((ISipRequestHandler*)&sipServer);
    cSniffer.SetHandler((ISipResponseHandler*)&sipServer);
    cSniffer.SetHandler((IEvtHandlerDTMF*)&dtmfHandler);

    // Create a handler for converting UDP messages to SIP
    CSipMessageHandler msgHandler;
    msgHandler.SetHandler((ISipRequestHandler*)&cSniffer);
    msgHandler.SetHandler((ISipResponseHandler*)&cSniffer);
    sipServer.SetSender(&msgHandler);

    // Listen for UDP messages
    CAsioUdpServer udpServer;
    udpServer.LocalEndpoint().Assign(config.ServerLocalEndpoint());
    udpServer.SetHandler(&msgHandler);
    msgHandler.SetSender(&udpServer);
    udpServer.Start();

    // Main loop
    #ifdef _WIN32
    while (!_kbhit())
    #else
    while (!g_bTerminate)
    #endif
    {
        cSwitch.Poll();
        cSniffer.Poll();
        udpServer.Poll();
    }

    return 0;
}