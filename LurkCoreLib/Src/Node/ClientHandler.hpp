#pragma once
#include "./../Network/TcpClient.hpp"
#include <future>
#include <iostream>

namespace Lurk {
    namespace Node {

        class ClientHandler{
            public:
                ClientHandler(Lurk::Network::TcpClient);
                std::future<int> SendAsync(const std::byte* buffer, int len);
            private:
                Lurk::Network::TcpClient client;
        };
    }
}

