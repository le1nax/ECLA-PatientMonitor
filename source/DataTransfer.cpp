#include "../include/DataTransfer.h"
#include "../include/definitions.h"

//PCANModule includes
#include "../PCANModule/DataManager.h"
#include "../PCANModule/DataPoint.h"
#include "../PCANModule/CanAdapter.h"

#include "../include/SocketClient.h"

#include <string.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <stdlib.h> 

#define MAX_BUFFER_SIZE 16
#pragma comment (lib, "ws2_32.lib")



DataTransfer::DataTransfer() : udp_signal_period{1000/udp_freq}
{
	init_msg_vec = make_bytes(
    0x0D, 0xEC, 0x05, 0x08, 0x13, 0x01, 0x00, 0x16, 0x01, 0x02, 0x80, 0x00, 0x14, 0x02, 0x00, 0x02
    );
	init_msg_char = reinterpret_cast<char*>(init_msg_vec.data());
	serverSetup();
}


void DataTransfer::serverSetup()
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
    {
		if(configModeDebug){
		std::cout <<  "Can't start Winsock! " << wsOk;
		}
		return;
	}
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

	// Create a server hint structure for the server
	sockaddr_in server;
	server.sin_addr.S_un.S_addr = ADDR_ANY; // Use any IP address available on the machine
	server.sin_family = AF_INET; // Address format is IPv4
	server.sin_port = htons(12345); // Convert from little to big endian

	// Try and bind the socket to the IP and port
	if (bind(serverSocket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		if(configModeDebug){ 
			std::cout <<  "Can't bind socket! " << WSAGetLastError() << std::endl;
		}
		return;
	}

	// Create client address structure
    int clientAddressSize = sizeof(clientAddress);

    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddress.sin_port = htons(12345);

    if (clientAddress.sin_addr.s_addr == INADDR_NONE)
    {
        std::cerr << "The target ip address entered must be a legal IPv4 address." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Resolve client hostname
    if (inet_pton(AF_INET, "127.0.0.1", &(clientAddress.sin_addr)) <= 0)
    {
        std::cerr << "Invalid address" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

}

bool DataTransfer::pollClientRequest()
{
	Sleep(2001);	

	////////////////////////////////////////////////////////////
	//// SERVER RECEIVES via WSARecvFrom
	////////////////////////////////////////////////////////////

	// sockaddr_in clientRecv; // Use to hold the client information (port / ip address)
	int clientRecvLength = sizeof(clientRecv); // The size of the client information

	char buffer1[MAX_BUFFER_SIZE];
	LPWSABUF lpwsabufferServer = new WSABUF();		
	lpwsabufferServer->len = sizeof(buffer1);

	DWORD bytesReceived1 = 0;
	DWORD flags2 = 0;

	ZeroMemory(&clientRecv, clientRecvLength); // Clear the client structure
	ZeroMemory(buffer1, MAX_BUFFER_SIZE); // Clear the receive buffer
	lpwsabufferServer->buf = buffer1;

		std::cout <<  "Polling Association Request..." << std::endl;
	
	// Receive from Client
	if (WSARecvFrom(serverSocket, lpwsabufferServer, 1, &bytesReceived1, &flags2,
		reinterpret_cast<sockaddr*>(&clientRecv), reinterpret_cast<LPINT>(&clientRecvLength), nullptr, nullptr) == SOCKET_ERROR)
		{
			std::cerr << "WSARecvFrom failed. Error code: " << WSAGetLastError() << std::endl;
			closesocket(serverSocket);
			WSACleanup();
			delete lpwsabufferServer;
		}

	// Display message and client info
	char clientIp[256]; // Create enough space to convert the address byte array
	ZeroMemory(clientIp, 256); // to std::string of characters

	// Convert from byte array to chars
	inet_ntop(AF_INET, &clientRecv.sin_addr, clientIp, 256);

	// Display the message / who sent it
	char* receivedAssociationMsg = lpwsabufferServer->buf;

	if(configModeDebug){ 
		std::cout <<  "Message recv from " << clientIp << " : " << lpwsabufferServer->buf << std::endl;
	}
	auto compareResult = compareMsgs(receivedAssociationMsg, init_msg_char, 16);
	if(compareResult != 1)
	{
			std::cout <<  "poll Request denied due to false association message" << std::endl;
		delete lpwsabufferServer;
		return false;
	}

	delete lpwsabufferServer;
	std::cout <<  "Poll Request successful" << std::endl;
	return true;
}

void DataTransfer::pcanConnect()
{
	TPCANHandle device = PCAN_USBBUS1;
	m_CanAdapter = std::make_unique<CanAdapter>(device);
	while (!m_CanAdapter->connect())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void DataTransfer::createPCANSendThread()
{
    if(pcanReadThread && pcanReadThread->joinable())
    {
        pcanReadThread->join(); 
    }
    pcanReadThread = std::make_unique<std::thread>(&DataTransfer::pcanSendData, this);
}


void DataTransfer::pcanSendData()
{
	while(1)
	{
		DataPoint data = m_CanAdapter->listen();

		////////////////////////////////////////////////////////////
		//// SERVER SENDS
		////////////////////////////////////////////////////////////
		if(configModeDebug){
			std::cout <<  "Server sent Data Point canID: " << data.encodedData.canID << std::endl;
			std::cout <<  "Server sent Data Point timestamp: " << data.encodedData.timestamp << std::endl;
			std::cout <<  "Server sent Data Point payload: " << data.encodedData.value << std::endl;
			std::cout <<  "Server sent Data Point pcantimestamp: " << data.encodedData.pcanTimestamp << std::endl;
		}
		auto dataSize = sizeof(data.encodedData);
		char buffer[dataSize];
		memcpy(buffer, &data.encodedData, dataSize);

		LPWSABUF lpwsabuf = new WSABUF();
		lpwsabuf->buf = buffer;
		lpwsabuf->len = sizeof(buffer);

		DWORD numBytesSent = 0;
		DWORD flags = 0;

		int wsaSendOK = WSASendTo(serverSocket, lpwsabuf, 1, reinterpret_cast<LPDWORD>(&numBytesSent), flags,
		reinterpret_cast<sockaddr*>(&clientRecv), sizeof(clientRecv), nullptr, nullptr);
		if (wsaSendOK == SOCKET_ERROR)
		{
			std::cout <<  "Error when calling WSASendTo: " << WSAGetLastError() << std::endl; 
		}
		delete lpwsabuf;
		if(configModeDebug){ 
			countMsgSend = countMsgSend + 1;
			std::cout <<  countMsgSend << std::endl;
		}

		// std::this_thread::sleep_for(std::chrono::milliseconds(udp_signal_period));
		// m_CanAdapter->skipDataPoints(udp_signal_period*3);
		// dataManagerInstance.sendData(data);
	}
}

DataTransfer::~DataTransfer()
{
    if(pcanReadThread && pcanReadThread->joinable()) {
        pcanReadThread->join();
    }
}


void DataTransfer::establishConnection()
{
	while(!pollClientRequest())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	pcanConnect(); 
	createPCANSendThread();
}
