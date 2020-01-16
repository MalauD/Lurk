#include "OnNewClientEventArgs.hpp"

Lurk::Node::OnNewClientEventArgs::OnNewClientEventArgs(Network::TcpClient client) : newClient(client)
{

}

Lurk::Network::TcpClient Lurk::Node::OnNewClientEventArgs::GetNewSocket()
{
	return newClient;
}
