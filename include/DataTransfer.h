#pragma once

#include "SocketClient.h"
#include "../PCANModule/CanAdapter.h"
#include <thread>

/// @brief Class, that manages the udp send thread and logs the data
class DataTransfer
{
    public:
        /// @brief Constructor that initializes the init message and the measurement vectors
        DataTransfer();
        virtual ~DataTransfer();
        /// @brief Establishes a connection to the client, by polling a request  init message
        void establishConnection();
    private:
        /// @brief Sets up server wsa configurations
        void serverSetup();
        /// @brief Polls a client request with wsa ReceiveFrom
        /// @return Retruns the outcome of Request Poll
        bool pollClientRequest();
        /// @brief Connects the USB PCAN module
        void pcanConnect();
        /// @brief Sends the PCAN Messages 
        void pcanSendData();
        /// @brief Creates an UDP Send Thread
        void createPCANSendThread();
        /// @brief Logs the measurement data in a CSV file
        /// @param data The Data Point to be logged
        void logData(DataPoint& data);

        /// @brief Measurements are stored in std::vectors which are stored in a std::vector measurementsVec. It is filled on runtime on runtime
        std::vector<std::vector<float>*> measurementsVec = {};

        /// @brief The measurements of Honeywell pressure
        std::vector<float> m_BPData_mBar = {};
        /// @brief The measurements of Honeywell temperature
        std::vector<float> m_TempData_Celsius = {};
        /// @brief The measurements of SFM3300 data
        std::vector<float> m_FlowData_mBar = {};
        /// @brief The predefined initMsg that is used to start an Association between server and client
        std::vector<std::byte> init_msg_vec;
        /// @brief The init Message as a char pointer
        char* init_msg_char;
        /// @brief Client Address information
        sockaddr_in clientRecv{};
        /// @brief WSA Server Socket
        SOCKET serverSocket;
        //sockaddr_in clientAddress{};

        /// @brief CanAdapter instance that manages the CAN Listening
        std::unique_ptr<CanAdapter> m_CanAdapter{};
        /// @brief Size of Client Adress wsa Struct
        int clientAddressSize;
        /// @brief Length of Client Receive Information
        int clientRecvLength;
        /// @brief Thread that manages the reading of PCANMessages
        std::unique_ptr<std::thread> pcanReadThread {nullptr};

        /// @brief debug value, if configModeDebug flag is true, Logging takes too much runtime so that the default signal rate can not be served. Consequently, DataPoints are skipped 
        int udp_signal_period;
        uint64_t countMsgSend = 0;
};