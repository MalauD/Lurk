#pragma once
#include <ws2tcpip.h>

namespace Lurk{
    namespace Network{
        class Socket{
            protected:
                virtual int Bind(const struct sockaddr *addr, socklen_t addrlen) = 0;
                virtual int Listen(int backlog) = 0;
                virtual Socket* Accept(struct sockaddr *addr, socklen_t addrlen) = 0;
                virtual int Connect(const struct sockaddr *addr, socklen_t addrlen) = 0;
                virtual int Send(const void* buffer, int len, int flags) = 0;
                virtual int Recv(const void* buffer, int len, int flags) = 0;
                SOCKET _socket;
                bool IsSocketAlive = false;
            public:
                operator int() const {return _socket;};
                bool operator==(int i) {return (_socket == i ? true : false);}
                bool IsAlive() {return IsSocketAlive;}
        }; 
    }
}