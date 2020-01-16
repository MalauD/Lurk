#include "ServerHandler.hpp"


Lurk::Node::ServerHandler::ServerHandler(int16_t port, std::unique_ptr<Lurk::Network::Socket> mySocket) : serv(std::move(mySocket), port)
{
	
}

Lurk::Network::TcpExceptions Lurk::Node::ServerHandler::Start()
{
	Lurk::Network::TcpExceptions excep;
	if ((excep = serv.SetupServer()) != Lurk::Network::TcpExceptions::NoException) {
		return excep;
	}

	serv.AcceptClients([this](auto newSocket, auto excep) {
			if (excep != Lurk::Network::TcpExceptions::AcceptError) {
				auto myClient = Lurk::Network::TcpClient(std::move(newSocket));
				std::thread([this, &myClient]() {
						OnNewClient.Call(OnNewClientEventArgs(myClient));
				});
				
			}
			//TODO implement error handling / logging
		});

	return Lurk::Network::TcpExceptions::NoException;
}
