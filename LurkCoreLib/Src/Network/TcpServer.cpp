#include "TcpServer.hpp"

using namespace Lurk::Network;

const sockaddr_in TcpServer::GetAddressFromPort(int16_t port){
    struct sockaddr_in mySeverAddr;
    mySeverAddr.sin_family = AF_INET;
    mySeverAddr.sin_addr.s_addr = INADDR_ANY;
    mySeverAddr.sin_port = htons(port);
    return mySeverAddr;
}

TcpServer::TcpServer(std::unique_ptr<Socket> socket, int16_t port) : Address(TcpServer::GetAddressFromPort(port)), _socket(std::move(socket)){
    
}

TcpServer::TcpServer(std::unique_ptr<Socket> socket) : Address(TcpServer::GetAddressFromPort(2003)), _socket(std::move(socket)) {
    
}

TcpExceptions TcpServer::SetupServer() {
    socklen_t addrlen = sizeof(Address);
    if(_socket->Bind((struct sockaddr *)&Address,addrlen)  < 0){
        return TcpExceptions::BindError;
    }

    if(_socket->Listen(5) < 0){
        return TcpExceptions::ListenError;
    }

    return TcpExceptions::NoException;
}

void TcpServer::AcceptClients(std::function<void(std::unique_ptr<Socket>, TcpExceptions)> callback){ 
    Socket *NewSocket;
    socklen_t AddrLen = sizeof(Address);
    if(!((NewSocket = _socket->Accept((struct sockaddr *)&Address, AddrLen))->operator==(INVALID_SOCKET))){
        callback(std::unique_ptr<Socket>(NewSocket), TcpExceptions::NoException);
    }
    else {
        callback(std::unique_ptr<Socket>(nullptr), TcpExceptions::AcceptError);
    }
}

void TcpServer::AcceptClientsAsync(std::function<void(std::unique_ptr<Socket>, TcpExceptions)> callback){
    Socket *NewSocket;
    socklen_t AddrLen = sizeof(Address);
    if(!((NewSocket = _socket->Accept((struct sockaddr *)&Address, AddrLen))->operator==(INVALID_SOCKET))){
        std::thread([&callback,&NewSocket](){
            callback(std::unique_ptr<Socket>(NewSocket), TcpExceptions::NoException);
            while(NewSocket->IsAlive()){
                std::this_thread::sleep_for(std::chrono::milliseconds(2)); //TODO Ugly
            }
                
        }).detach();
    }
}