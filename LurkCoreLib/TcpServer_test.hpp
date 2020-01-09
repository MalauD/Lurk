#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Src/Network/TcpServer.hpp"
#include "Test/Network/SocketMock.hpp"

using namespace Lurk::Network;
using ::testing::_;
using ::testing::Return;

TEST(TcpServerTest, SetupServerTest) {
	MockSocket* mock = new MockSocket();
	auto server = TcpServer(std::unique_ptr<MockSocket>(mock));

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(-1));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::BindError);

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Listen(_))
		.Times(1)
		.WillOnce(Return(-1));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::ListenError);

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Listen(_))
		.Times(1)
		.WillOnce(Return(0));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::NoException);
}

TEST(TcpServerTest, SetupServerPortTest) {
	MockSocket* mock = new MockSocket();
	auto server = TcpServer(std::unique_ptr<MockSocket>(mock), 2003);

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(-1));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::BindError);

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Listen(_))
		.Times(1)
		.WillOnce(Return(-1));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::ListenError);

	EXPECT_CALL(*mock, Bind(_, _))
		.Times(1)
		.WillOnce(Return(0));

	EXPECT_CALL(*mock, Listen(_))
		.Times(1)
		.WillOnce(Return(0));

	ASSERT_EQ(server.SetupServer(), TcpExceptions::NoException);
}