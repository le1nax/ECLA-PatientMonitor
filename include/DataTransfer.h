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
};