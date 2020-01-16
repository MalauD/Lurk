#include "TcpClient.hpp"

using namespace Lurk::Network;

int TcpClient::inet_pton(int af, const char *src, void *dst)
{
  return ::inet_pton(af, (PCSTR)src, dst);
}

TcpClient::TcpClient(std::unique_ptr<Socket> socket) : _socket(std::move(socket)){
 
}

TcpExceptions TcpClient::ConnectToServer(char* ip, int16_t port) {
    struct sockaddr_in myServerAddr;
    myServerAddr.sin_family = AF_INET;
    myServerAddr.sin_port = htons(port);

    if(TcpClient::inet_pton(AF_INET, ip, &myServerAddr.sin_addr) <= 0){
        return TcpExceptions::InvalidAddress;
    } 

    if(_socket->Connect((struct sockaddr *)&myServerAddr, sizeof(myServerAddr)) < 0){
        return TcpExceptions::ConnectionError;
    }

    return TcpExceptions::NoException;
}

int TcpClient::SendBytes(const uint8_t* buffer, int len) {
    return _socket->Send(buffer, len, 0);
}

int TcpClient::RecvBytes(const uint8_t* buffer, int len) {
    return _socket->Recv(buffer, len, 0);
}

void TcpClient::RecvBytesAsync(std::function<void(uint8_t*,int)> callback){
    uint8_t buffer[1024];
    std::thread([this, &buffer, &callback](){
        int i = RecvBytes(buffer,1024);
        callback(buffer,i);
    }).detach();
}

void TcpClient::RecvBytesLoopAsync(std::function<void(uint8_t*,int)> callback){
    
    std::thread([this, callback](){
        uint8_t buffer[1024];
        int i = 1;
        while(i != 0){
            i = RecvBytes(buffer,1024);
            callback(buffer,i);
            memset(buffer,0,sizeof(buffer));
        }
        //_socket->IsSocketAlive = false;
    }).detach();
}
