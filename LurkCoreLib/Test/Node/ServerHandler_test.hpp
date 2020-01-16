#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./../Network/SocketMock.hpp"
#include "./../../Src/Node/ServerHandler.hpp"

using namespace Lurk::Node;
using ::testing::_;
using ::testing::Return;

TEST(ServerHandlerTest, Start_test) {
	MockSocket* mock = new MockSocket();
	auto handler = ServerHandler(2003, std::unique_ptr<MockSocket>(mock));

	handler.OnNewClient.Subscribe([&](OnNewClientEventArgs args) {
		ASSERT_TRUE(true);
	});

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Listen(_))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Accept(_, _))
		.Times(1)
		.WillOnce(Return(new MockSocket()));

	ASSERT_EQ(handler.Start(), Lurk::Network::TcpExceptions::NoException);

	Sleep(100);
}