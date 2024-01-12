#pragma once

#include "SocketClient.h"
#include "../PCANModule/CanAdapter.h"
#include <thread>

class DataTransfer
{
    public:
        DataTransfer();
        virtual ~DataTransfer();
        void establishConnection();
    private:
        void serverSetup();
        bool pollClientRequest();
        void pcanConnect();
        void pcanSendData();
        void createPCANSendThread();
        void logData(DataPoint& data);


        std::ofstream csvFile;

        /// @brief Measurements are stored in std::vectors which are stored in a std::vector measurementsVec. It is filled on runtime on runtime
        std::vector<std::vector<float>*> measurementsVec = {};

        /// @brief The measurements of Honeywell pressure
        std::vector<float> m_BPData_mBar = {};
        /// @brief The measurements of Honeywell temperature
        std::vector<float> m_TempData_Celsius = {};
        /// @brief the measurements of SFM3300 data
        std::vector<float> m_FlowData_mBar = {};
        std::vector<std::byte> init_msg_vec;
        char* init_msg_char;
        sockaddr_in clientRecv{};
        SOCKET serverSocket;
        sockaddr_in clientAddress{};
        std::unique_ptr<CanAdapter> m_CanAdapter{};
        int clientAddressSize;
        int clientRecvLength;
        std::unique_ptr<std::thread> pcanReadThread {nullptr};
        int udp_signal_period;
        uint64_t countMsgSend = 0;

        size_t currentCsvSize = 0;
};