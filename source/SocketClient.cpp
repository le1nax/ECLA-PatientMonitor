#include "../include/SocketClient.h"
#include <sstream>
#include <thread>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <string>
#include <filesystem>
#include <cmath>
#include <vector>
#include <regex>

using namespace std;

SocketClient::SocketClient(std::string remoteIPtarget, const unsigned short remotePortTarget) : 
    UDPSocket(), m_remoteIPtarget(remoteIPtarget), m_port(remotePortTarget) //, m_udpState(*this)
 {
//     struct sockaddr_in RecvAddr;
//     RecvAddr.sin_family = AF_INET;
//     RecvAddr.sin_port = htons(m_port);
//     RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

//     if (bind(sock, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr)) != 0) {
//     /* Bind to the socket failed */
//     wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
//     closesocket(sock);
//     WSACleanup();
//     }
    // setup remote server address structure
    memset((void *)&m_sa_remoteIPtarget, '\0', sizeof(struct sockaddr_in));
    m_sa_remoteIPtarget.sin_family = AF_INET; //ipv4
    m_sa_remoteIPtarget.sin_port = htons(m_port); //htons converts port number from host byte order to network byte order
    inet_pton(AF_INET, m_remoteIPtarget.c_str(), &(m_sa_remoteIPtarget.sin_addr)); //corresponds to m_sa_remoteIPtarget.sin_addr.s_addr = inet_addr(m_remoteIPtarget)

    // connect client socket to remote IP and port
   // Connect(m_sa_remoteIPtarget);


    if(configModeDebug){
         std::cout <<  "Created and initialised client" << std::endl;
    }
}

SOCKET SocketClient::getSocket()
{
    return sock;
}

void SocketClient::sendBytes(vector<std::byte> bytes)
{
     ///@todo prüfen ob das funktioniert
    size_t len = bytes.size();
    char* charBytes = reinterpret_cast<char*>(bytes.data()); 

    uint32_t numBytesSent = SendTo(m_sa_remoteIPtarget, charBytes, len, 0);
}


void SocketClient::ProcessPacket(char* buffer)
{
    if(configModeDebug){ 
        std::cout <<  "finished ProcessPacket" << std::endl;
    }
}

void SocketClient::Receive(char* buffer1, size_t buffersize, int flags)
{
    Receive_State state;
    WSADATA wsaData;
    WSABUF DataBuf;
    
    struct sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof (SenderAddr);
    state.state_ip = SenderAddr;
    state.numBytesReceived = 0;
    state.numBytesTransferred = 0;
    
    
    char RecvBuf[buffersize];
    int BufLen = buffersize;
    DataBuf.len = BufLen;
    DataBuf.buf = RecvBuf;
    state.wsaBuf = DataBuf;

    DWORD Flags = 0;

    int err = 0;
    int rc;
    int retval = 0;
    
    // Make sure the Overlapped struct is zeroed out
    SecureZeroMemory((PVOID) &state.overlapped, sizeof(WSAOVERLAPPED) );

    // Create an event handle and setup the overlapped structure.
    state.overlapped.hEvent = WSACreateEvent();
    if (state.overlapped.hEvent == NULL) {
    wprintf(L"WSACreateEvent failed with error: %d\n", WSAGetLastError());
    WSACleanup();
    return;
    }
    

    m_sa_remoteIPtarget.sin_family = AF_INET;
    m_sa_remoteIPtarget.sin_port = htons(m_port);
    m_sa_remoteIPtarget.sin_addr.s_addr = htonl(INADDR_ANY);
    
    std::string targetip = m_remoteIPtarget; 
    inet_pton(AF_INET, targetip.c_str(), &(m_sa_remoteIPtarget.sin_addr));

    wprintf(L"Listening for incoming datagrams on port=%d\n", m_port);
    rc = WSARecvFrom(sock,
              &state.wsaBuf,
              1,
              &state.numBytesReceived,
              &Flags,
              (SOCKADDR *) & SenderAddr,
              &SenderAddrSize, &state.overlapped, NULL);

    if (rc != 0) {
    err = WSAGetLastError();
    if (err != WSA_IO_PENDING) {
        wprintf(L"WSARecvFrom failed with error: %ld\n", err);
        WSACloseEvent(state.overlapped.hEvent);
        closesocket(sock);
        WSACleanup();
        return;
    }
    else {
        rc = WSAWaitForMultipleEvents(1, &state.overlapped.hEvent, TRUE, INFINITE, TRUE);
        if (rc == WSA_WAIT_FAILED) {
        wprintf(L"WSAWaitForMultipleEvents failed with error: %d\n", WSAGetLastError());
        retval = 1;
        }

        rc = WSAGetOverlappedResult(sock, &state.overlapped, &state.numBytesReceived,
                FALSE, &Flags);
        if (rc == FALSE) {
        wprintf(L"WSArecvFrom failed with error: %d\n", WSAGetLastError());
        retval = 1;
        }
        else{
        state.numBytesReceived += state.numBytesTransferred;

        if (state.numBytesReceived > 0)
        {
			    // Receive operation completed successfully
			    ReceiveCallback(0, state.numBytesReceived, &state.overlapped); //go and process data
        }
        wprintf(L"Number of received bytes = %d\n", state.numBytesReceived);
        readBytesFromArray(state.wsaBuf.buf, state.numBytesReceived);

        }
        
        wprintf(L"Finished receiving.\n");
        cout << "Message recv: " << DataBuf.buf << endl;
    }
    
    }
    //---------------------------------------------
    // When the application is finished receiving, close the socket.

    // WSACloseEvent(state.overlapped.hEvent);
    // closesocket(sock);
    // wprintf(L"Exiting.\n");

    //---------------------------------------------
    // Clean up and quit.
    // WSACleanup();
    m_lastMsg = state.wsaBuf.buf;
    lastMsgSize = state.wsaBuf.len;
    return;
}




/// @todo add path_to_file

void CALLBACK SocketClient::ReceiveCallback(DWORD errorCode, DWORD numBytesReceived, LPWSAOVERLAPPED overlapped, DWORD flags)
{
    //std::unique_ptr<ReceiveState> state = std::make_unique<ReceiveState>(*CONTAINING_RECORD(overlapped, ReceiveState, overlapped));

    Receive_State state = *CONTAINING_RECORD(overlapped, Receive_State, overlapped);
        //das eine overlapped, um vom member auf die Klasse zu kommen
        //das andere als memory offset um den Zeiger auf Receive_State zu bekommen
 
        //The purpose of the macro is to obtain a pointer to the containing structure given a pointer to one of its members. 
        //The specified member is used only to determine the offset of that member within the containing structure.

    if (errorCode == 0) 
    {
/*
		//read the number of bytes received from the buffer into receivedData
    std::string receivedData(*(state.buffer), numBytesReceived); 

		    // Convert buffer to std::vector<byte> if needed
	        // B: std::vector<std::byte> data_bytes(udpState.state_client.buffer, udpState.state_client.buffer + numBytesReceived);

    //im cs code: string path = Path.Combine(Directory.GetCurrentDirectory(),Globals.pathFile+"_Philips_MPrawoutput.txt");
		std::string path_to_file = ""; //////////////////////////////////////////////////

		// Write data to file
    bool writing_to_file_successful = ByteArrayToFile(path_to_file, receivedData);
	        // B: bool writing_to_file_successful2 = ByteArrayToFile(path_to_file, data_bytes, numBytesReceived);
*/
    if(configModeDebug){
         std::cout <<  "now processing packet" << std::endl;
    //ProcessPacket(state.wsaBuf.buf);
    }

    }
    else
    {
    std::cerr << "ReceiveCallback error: " << WSAGetLastError() << std::endl;
    // Handle the error
    // ... //
    }

    //zur Sicherheit. koennte theoretisch weg, weil danach eh in Receive hEvent geclosed wird, aber muesste wieder rein, falls daran mal was geaendert wird
    WSAResetEvent(state.overlapped.hEvent); 
}


void SocketClient::establishLanConnection() 
{
    if(configModeDebug){ 
        std::cout <<  "establishing Lan Connection" << std::endl;
    }
        //Receive AssociationResult message 
			///@todo schauen wie viel Buffer space wir brauchen (chapter4 p.29 sagt 1380 ->testen)
					//try:
			//Receive MDSCreateEventReport message
        char readassocbuffer[1380] = ""; 
        if(configModeDebug){ 
            std::cout <<  "readassbuffer" << std::endl;
        }
        Receive(readassocbuffer);
        if(configModeDebug){ 
            std::cout <<  "end read assbuffer" << std::endl;
        }
}

void SocketClient::ThreadReceive(char* receivedBuffer)
{
    while (!stopThreadReceive)
    {
    Receive(receivedBuffer);
    //std::this_thread::sleep_for(std::chrono::milliseconds(m_receiveInterval));
    }
}

