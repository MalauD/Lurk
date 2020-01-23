#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./../Network/SocketMock.hpp"
#include "./../../Src/Network/TcpClient.hpp"
#include "./../../Src/Node/ClientHandler.hpp"

using namespace Lurk::Node;
using ::testing::_;
using ::testing::Return;

TEST(ClientHandlerTest, Ctor_test) {
	MockSocket* mock = new MockSocket();
	ClientHandler handler(Lurk::Network::TcpClient(std::unique_ptr<Socket>(mock)));

	EXPECT_
}