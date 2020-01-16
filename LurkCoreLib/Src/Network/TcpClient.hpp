#pragma once
#include "TcpSocket.hpp"
#include "./Exceptions/TcpExceptions.hpp"
#include <stdint.h>
#include <cstring>
#include <thread>
#include <functional>
#include <memory>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace Lurk{
    namespace Network{
        class TcpClient{
            public:
                TcpClient(std::unique_ptr<Socket> socket);
                TcpExceptions ConnectToServer(char* ip, int16_t port);
                int SendBytes(const uint8_t* buffer, int len);
                int RecvBytes(const uint8_t* buffer, int len);
                void RecvBytesAsync(std::function<void(uint8_t*,int)> callback);
                void RecvBytesLoopAsync(std::function<void(uint8_t*,int)> callback);
                static int inet_pton(int af, const char* src, void* dst);
            private:
                std::shared_ptr<Socket> _socket;
        };
    }
}