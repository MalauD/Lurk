#pragma once
#include <future>
#include "./../Network/TcpServer.hpp"
#include "./../Event/Event.hpp"
#include "./EventsArgs/OnNewClientEventArgs.hpp"
#include "./EventsArgs/OnAcceptClientErrorEventArgs.hpp"

namespace Lurk {
    namespace Node {

        class ServerHandler {
            public:
                ServerHandler(int16_t port, std::unique_ptr<Lurk::Network::Socket> socket);
                Lurk::Network::TcpExceptions Start();
                void Stop();
                Lurk::Event::Event<OnNewClientEventArgs> OnNewClient;
                Lurk::Event::Event<OnAcceptClientErrorEventArgs> OnAcceptClientError;
            private:
                Lurk::Network::TcpServer serv;
                bool isRunning =  false;
        };
    }
}

 