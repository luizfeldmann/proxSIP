#include <proxSIP/CAsioUdpServer.h>
#include <conio.h>

int main(int argc, char** argv)
{
    CAsioUdpServer server;
    server.LocalEndpoint().Assign("192.168.0.12", 5060);
    server.Start();

    while (!_kbhit())
        server.Poll();

    return 0;
}