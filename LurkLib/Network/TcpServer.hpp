#pragma once
#include "TcpClient.hpp"
#include "./Exceptions/TcpExceptions.hpp"
#include <stdint.h>
#include <winsock2.h>
#include <mutex>
#include <condition_variable>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
#include <functional>

namespace Lurk{
    namespace Network{
        class TcpServer : public TcpSocket{
            public:
                TcpServer();
                TcpServer(int16_t port);
                TcpExceptions SetupServer();
                void AcceptClients(std::function<void(TcpClient*, TcpExceptions)> callback);
                void AcceptClientsAsync(std::function<void(TcpClient*, TcpExceptions)> callback);
            private:
                sockaddr_in Address;
                static const sockaddr_in GetAddressFromPort(int16_t port);

        };
    }
}