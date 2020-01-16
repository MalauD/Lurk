#pragma once
#include "./../../Event/EventArgs.hpp"
#include "./../../Network/TcpClient.hpp"

namespace Lurk {
	namespace Node {
		class OnNewClientEventArgs : public Event::EventArgs
		{
			public:
				OnNewClientEventArgs(Network::TcpClient client);
				Network::TcpClient GetNewSocket();
			private:
				Network::TcpClient newClient;
		};
	}
}

		

