#pragma once
/// SocketClient is the Client class
///
/// It processes the protocol dialog between Monitor and Client
#include "Socket.h"


#define RECEIVEINTERVAL 500 // koennen den receive thread nicht komplett durchlaufen lassen weil wir keinen echten Parallelismus haben


///@brief The SocketClient class is derived from the UDPSocket class and implements the UDP client connecting to the patient monitor and processing the received data
class SocketClient : public UDPSocket {

    public:
        /// @brief Constructor of class SocketClient
        /// @param remoteIPtarget the IP address to send to
        /// @param remotePortTarget the port of the target address
        /// @todo Konstruktor soll die membervariablen initialisieren
        SocketClient(std::string remoteIPtarget, const unsigned short remotePortTarget);
        ~SocketClient() = default;
        
        /// @brief A method to establish a LAN connection to the monitor, keep the connection alive and exchange data
        void establishLanConnection();

        /// @brief a getter method for the SOCKET sock
        /// @return the membervariable SOCKET sock
        SOCKET getSocket();
        
        sockaddr_in m_sa_remoteIPtarget;
        /// @brief A method for receiving data from the server
        /// @param buffer1 the buffer that contains the data
        /// @param buffersize the size of the buffer
        /// @param flags the flags to set for the base WSARecvFrom function
        void Receive(char* buffer, size_t buffersize = maxbuffersize, int flags = 0);
    private:
        /// @brief A method to send the specified bytes to the target address by putting them in a buffer and sending them via SendTO()
        /// @param bytes the bytes to be sent 
        void sendBytes(std::vector<std::byte> bytes);

        /// @brief Processes all incoming types of data protocols
        /// @param buffer char array with the sent bytes
        void ProcessPacket(char* buffer);

        ///@brief Logging variable (Last message received)
        char* m_lastMsg;
        size_t lastMsgSize = 0;

        std::string m_remoteIPtarget = "";
        std::string m_strTimestamp = "";
        std::string m_DeviceID= "";
        std::string m_idlabelstring = "";
        const unsigned short m_port = 0; 
        
        /// @brief A method to convert int to unsigned char
        /// @param value the int value to be converted
        /// @return the unsgined char
        unsigned char ConvertToByte(int value);
        
        /// @brief A method to check if data is in little endian format
        /// @return true if it is little endian
        bool IsLittleEndian();

        private:
      
        void SendRTSAPriorityMessage(std::vector<std::byte> WaveTrType);
        /// @brief A method for the thread that repeatedly sends an extended poll data request
        /// @param nInterval the time interval between polls
        void SendCycledExtendedPollDataRequest(size_t nInterval);
        /// @brief A method for the thread that repeatedly sends an extended poll wave data request
        /// @param nInterval the time interval between polls
        void SendCycledExtendedPollWaveDataRequest(size_t nInterval);

        
        /// @brief the Callback function to be called whenever a data packet has been received to process the data
        /// @param errorCode the error code from the receive operation
        /// @param numBytesReceived the number of bytes received
        /// @param overlapped the WSAOverlapped structure from the receive function
        /// @param flags the flags from the WSARecvFrom function
        void CALLBACK ReceiveCallback(DWORD errorCode, DWORD numBytesReceived, LPWSAOVERLAPPED overlapped, DWORD flags = 0);

        bool stopThreadKeepConnectionAlive = false;
        bool stopThreadReceive = false;
        int m_receiveInterval = RECEIVEINTERVAL;
        /// @brief the thread that repeatedly rechecks the MDS attributes
        /// @param nInterval the time interval
        void ThreadKeepConnectionAlive(int nInterval = 0);
        /// @brief the thread tha trepeatedly calls the Receive function to receive answers and wave and numeric data from the monitor
        /// @param receivedBuffer the buffer to pass to the Receive function
        void ThreadReceive(char* receivedBuffer);

        ///@brief Logging
        char* getLastMessage();

};

///current state of the client for the asynchronous receiving of data
class Receive_State 
{
    public:
        Receive_State() = default;
        ~Receive_State() = default;

        WSAOVERLAPPED overlapped; ///nötig um auf hEvent und overlap operation params zuzugreifen
        WSABUF wsaBuf;
        sockaddr_in state_ip;
        long unsigned int numBytesReceived;
        long unsigned int numBytesTransferred;
};