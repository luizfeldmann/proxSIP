#include <proxSIP/CAsioUdpServer.h>
#include <proxSIP/CSipMessageHandler.h>
#include <proxSIP/CSipServer.h>
#include <proxSIP/CAuthValidator.h>
#include <proxSIP/CSipRegistry.h>
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

    // Create the server logic
    CSipServer sipServer;

    // Create registry for contacts
    CSipRegistry cRegistry;
    sipServer.SetRegistry(&cRegistry);

    // Create auth manager
    CAuthValidator cAuth;
    cAuth.SetAccounts(config.GetUsers());
    sipServer.SetAuth(&cAuth);

    // Create a handler for converting UDP messages to SIP
    CSipMessageHandler msgHandler;
    msgHandler.SetHandler((ISipRequestHandler*)&sipServer);
    msgHandler.SetHandler((ISipResponseHandler*)&sipServer);
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
        udpServer.Poll();
    }

    return 0;
}