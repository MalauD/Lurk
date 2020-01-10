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

TEST(TcpServerTest, AcceptClientsTest) {
	MockSocket* mock = new MockSocket();
	auto server = TcpServer(std::unique_ptr<MockSocket>(mock), 2003);

	MockSocket* producedMock = new MockSocket();

	EXPECT_CALL(*mock, Accept(_, _))
		.Times(1)
		.WillOnce(Return(new MockSocket(INVALID_SOCKET)));

	server.AcceptClients([](std::unique_ptr<Socket> mySocket, TcpExceptions excep) {
			ASSERT_FALSE(mySocket);
			ASSERT_EQ(excep, TcpExceptions::AcceptError);
		});
	
	EXPECT_CALL(*mock, Accept(_, _))
		.Times(1)
		.WillOnce(Return(new MockSocket(1)));

	server.AcceptClients([](std::unique_ptr<Socket> mySocket, TcpExceptions excep) {
			ASSERT_TRUE(mySocket);
			ASSERT_EQ(excep, TcpExceptions::NoException);
		});



}

TEST(TcpServerTest, AcceptClientsAsyncTest) {
	MockSocket* mock = new MockSocket();
	auto server = TcpServer(std::unique_ptr<MockSocket>(mock), 2003);

	

	EXPECT_CALL(*mock, Accept(_, _))
		.Times(1)
		.WillOnce(Return(new MockSocket(INVALID_SOCKET)));

	server.AcceptClientsAsync([](std::unique_ptr<Socket> mySocket, TcpExceptions excep) {
			ASSERT_FALSE(mySocket);
			ASSERT_EQ(excep, TcpExceptions::AcceptError);
		});
}