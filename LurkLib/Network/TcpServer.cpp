#include "TcpServer.hpp"

using namespace Lurk::Network;

const sockaddr_in TcpServer::GetAddressFromPort(int16_t port){
    struct sockaddr_in mySeverAddr;
    mySeverAddr.sin_family = AF_INET;
    mySeverAddr.sin_addr.s_addr = INADDR_ANY;
    mySeverAddr.sin_port = htons(port);
    return mySeverAddr;
}

TcpServer::TcpServer(int16_t port) : Address(TcpServer::GetAddressFromPort(port)){
    
}

TcpServer::TcpServer() : Address(TcpServer::GetAddressFromPort(2003)){
    
}

TcpExceptions TcpServer::SetupServer() {
    socklen_t addrlen = sizeof(Address);
    if(Bind((struct sockaddr *)&Address,addrlen)  < 0){
        return TcpExceptions::BindError;
    }

    if(Listen(5) < 0){
        return TcpExceptions::ListenError;
    }

    return TcpExceptions::NoException;
}

void TcpServer::AcceptClients(std::function<void(TcpClient*, TcpExceptions)> callback){ 
    while(1){
        Socket *NewSocket;
        socklen_t AddrLen = sizeof(Address);
        if(!((NewSocket = Accept((struct sockaddr *)&Address, AddrLen))->operator==(INVALID_SOCKET))){
            callback((TcpClient*)NewSocket, TcpExceptions::NoException);
        }
    }
}

void TcpServer::AcceptClientsAsync(std::function<void(TcpClient*, TcpExceptions)> callback){ 
    while(1){
        Socket *NewSocket;
        socklen_t AddrLen = sizeof(Address);
        if(!((NewSocket = Accept((struct sockaddr *)&Address, AddrLen))->operator==(INVALID_SOCKET))){
            std::thread([&callback,&NewSocket](){
                callback((TcpClient*)NewSocket, TcpExceptions::NoException);
                while(NewSocket->IsAlive()){
                    std::this_thread::sleep_for(std::chrono::milliseconds(2)); //TODO Ugly
                }
                
            }).detach();
        }
    }
}