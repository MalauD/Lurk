#include "TcpSocket.hpp"

using namespace Lurk::Network;

TcpSocket::TcpSocket(){
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    BOOL opt = FALSE;
    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR , (char *) &opt, sizeof(BOOL));
    IsSocketAlive = true;
}

TcpSocket::TcpSocket(SOCKET socket) {
    _socket = socket;
    IsSocketAlive = true;
}

int TcpSocket::Bind(const struct sockaddr *addr, socklen_t addrlen) {
    return bind(_socket,addr, addrlen);
}

int TcpSocket::Listen(int backlog) {
    return listen(_socket,backlog);
}

Socket* TcpSocket::Accept(struct sockaddr *addr, socklen_t addrlen) {
    return new TcpSocket(accept(_socket, addr, &addrlen));
}

int TcpSocket::Connect(const struct sockaddr *addr, socklen_t addrlen) {
    return connect(_socket, addr, addrlen);
}

int TcpSocket::Send(const void* buffer, int len, int flags){
    return send(_socket, (char *)buffer, len, flags);
}

int TcpSocket::Recv(const void* buffer, int len, int flags){
    return recv(_socket, (char *)buffer, len, flags);
}

bool TcpSocket::IsValid(){
    return !operator==((int)INVALID_SOCKET);
}
