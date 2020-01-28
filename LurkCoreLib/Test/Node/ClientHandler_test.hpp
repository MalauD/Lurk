#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./../Network/SocketMock.hpp"
#include "./../../Src/Network/TcpClient.hpp"
#include "./../../Src/Node/ClientHandler.hpp"
#include "./../../Src/Schemas/Version_generated.h"

using namespace Lurk::Node;
using ::testing::_;
using ::testing::Return;

TEST(ClientHandlerTest, Ctor_test) {
	MockSocket* mock = new MockSocket();
	ClientHandler handler(Lurk::Network::TcpClient(std::unique_ptr<Socket>(mock)));
}