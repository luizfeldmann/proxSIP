#include <proxSIP/CAsioUdpServer.h>
#include <proxSIP/CSipMessageHandler.h>
#include <proxSIP/CSipServer.h>
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

    // Create a handler for converting UDP messages to SIP
    CSipMessageHandler msgHandler;
    msgHandler.SetHandler((ISipRequestHandler*)&sipServer);
    msgHandler.SetHandler((ISipResponseHandler*)&sipServer);

    // Listen for UDP messages
    CAsioUdpServer udpServer;
    udpServer.LocalEndpoint() = config.ServerLocalEndpoint();
    udpServer.SetHandler(&msgHandler);
    udpServer.Start();

    // Main loop
    while (!_kbhit())
    {
        udpServer.Poll();
    }

    return 0;
}