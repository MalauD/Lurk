// #include "ServerHandler.hpp"


// ServerHandler::ServerHandler(int16_t port){
//     serv = Lurk::Network::TcpServer(port);
// }

// void ServerHandler::Start(){
//     serv.SetupServer();
    
//     serv.AcceptClientsAsync([this](Lurk::Network::TcpClient* cl, Lurk::Network::TcpExceptions te){
//         OnNewClient(cl, te);
//     });
// }
