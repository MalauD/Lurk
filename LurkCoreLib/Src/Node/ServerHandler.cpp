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

	isRunning = true;

	while (isRunning) {
			serv.AcceptClients([this](auto newClient, auto exceptAccept) {
				if (exceptAccept == Lurk::Network::TcpExceptions::NoException) {
					OnNewClient.Call(Lurk::Node::OnNewClientEventArgs(std::move(newClient)));
				}
				else if (exceptAccept == Lurk::Network::TcpExceptions::AcceptError) {
					OnAcceptClientError.GetFunc() ?
						OnAcceptClientError.Call(Lurk::Node::OnAcceptClientErrorEventArgs())
						: Stop();
				}
			});
	}



	return Lurk::Network::TcpExceptions::NoException;
}

void Lurk::Node::ServerHandler::Stop() 
{
	isRunning = false;
}