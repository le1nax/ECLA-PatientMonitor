#include "include/SocketClient.h"
#include "include/Program.h"

#include <string.h>
#include <thread>
#include <iostream>
#include <chrono>

#include <imgui.h>
#include <stdio.h>



#pragma comment (lib, "ws2_32.lib")

#define REMOTEIP "169.254.0.1"
#define REMOTEPORT 24105

#define LOCALIP "127.0.0.1"
#define LOCALPORT 69696

#define MAX_BUFFER_SIZE 2001

using namespace std;

uint16_t extractNumber(const char* charArray);
uint16_t convertBigEndianToLittleEndian(const char* charArray);
int main()
{
    try
   {
        unique_ptr<WSASession> Session = make_unique<WSASession>();

        const std::string s_remoteIP = REMOTEIP;
        const unsigned short remotePort = REMOTEPORT;
        unique_ptr<SocketClient> client = make_unique<SocketClient>(s_remoteIP, remotePort);

        client->establishLanConnection();
    }
    catch (std::exception &ex) //catch any occurring system errors
    {
        std::cout << ex.what();  //print error message
    }

    std::cin.get();

    // const char* buffer = "\x04\x01";
    // int ans = 0;
    // //ans = ReadByteValuesFromBuffer(buffer, 0, 3);
    // ans = Read16ByteValuesFromBuffer(buffer, 0);
    // std::cout << ans << std::endl;
    return 0;
}
// static uint16_t Read16ByteValuesFromBuffer(const char* buffer, size_t startIndex) {
//     uint16_t number = 0;
//     const char* buffer1 = buffer;

//     for (size_t i = startIndex; i < uInt16Size+startIndex; ++i) {
//         number = (number << 8) | static_cast<uint16_t>(buffer1[i]);
//     }
//     return number;
// }


// int main()
// {
//     try
//    {
//         unique_ptr<WSASession> Session = make_unique<WSASession>();

//         const std::string s_remoteIP = LOCALIP;
//         const unsigned short remotePort = LOCALPORT;
//         unique_ptr<SocketClient> client = make_unique<SocketClient>(s_remoteIP, remotePort);

//         client->SendWaveAssociationRequest();
//         std::cout << "sent" << std::endl;
//         // std::cin.get();// Wait for user input before exiting
//         char buffer[maxbuffersize];
//         std::cout << "begin receive" << std::endl;
//         client->Receive(buffer);
//     }
//     catch (std::exception &ex) //catch any occurring system errors
//     {
//         std::cout << ex.what();  //print error message
//     }
//     return 0;
// }


