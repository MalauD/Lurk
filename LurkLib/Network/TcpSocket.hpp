#pragma once
#include "Socket.hpp"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


namespace Lurk{
    namespace Network{
        class TcpSocket : public Socket{
            protected:
                TcpSocket(SOCKET socket);
                TcpSocket();
                int Bind(const struct sockaddr *addr, socklen_t addrlen) override;
                int Listen(int backlog) override;
                Socket* Accept(struct sockaddr *addr, socklen_t addrlen) override;
                int Connect(const struct sockaddr *addr, socklen_t addrlen) override;
                int Send(const void* buffer, int len, int flags) override;
                int Recv(const void* buffer, int len, int flags) override;
                bool IsValid();
                
        };
    }
}