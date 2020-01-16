#pragma once
#include "./../Network/TcpServer.hpp"
#include "./../Event/Event.hpp"
#include "./EventsArgs/OnNewClientEventArgs.hpp"

namespace Lurk {
    namespace Node {

        typedef Event::Event<OnNewClientEventArgs> OnNewClientEventType;

        class ServerHandler {
            public:
                ServerHandler(int16_t port, std::unique_ptr<Lurk::Network::Socket> socket);
                Lurk::Network::TcpExceptions Start();
                OnNewClientEventType OnNewClient;
            private:
                Lurk::Network::TcpServer serv;
        };
    }
}

 