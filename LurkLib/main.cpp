#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")


//#define _CRTDBG_MAP_ALLOC  
#ifdef _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#include "Event/ServerEvents/ServerEventArgs.hpp"
#include "Network/TcpClient.hpp"


int main() {
	WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

    

    Sleep(1);
    // TcpServer serv = TcpServer(2003);
    // if(serv.SetupServer() != 0){
    //     std::cout << WSAGetLastError();
    //     return -1;
    // }
    // serv.AcceptClientsAsync([](TcpClient* NewCl,TcpExceptions){
    //     NewCl->RecvBytesLoopAsync([](uint8_t* buf,int) {
    //         std::cout << buf;
    //         delete buf;
    //     });
    // });

    WSACleanup();
    
    while(1){}; 
    return 0;
}