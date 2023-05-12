#include <proxSIP/CAsioUdpServer.h>
#include <proxSIP/CSipMessageHandler.h>
#include <proxSIP/CSipServer.h>
#include <proxSIP/CAuthValidator.h>
#include "CAppConfig.h"
#include <iostream>
#include <conio.h>
#include "version.h"

int main(int argc, char** argv)
{
    // Print the header text
    std::cout << APPLICATION_NAME << " [v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "." << VERSION_TWEAK << "]" << std::endl;

    // Read configutation
    const char* szConfigPath = nullptr;

    if (argc == 2)
        szConfigPath = argv[1];

    CAppConfig config(szConfigPath);

    // Create the server logic
    CSipServer sipServer;

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
    while (!_kbhit())
    {
        udpServer.Poll();
    }

    return 0;
}