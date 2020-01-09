#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./../../Src/Network/TcpClient.hpp"
#include "./SocketMock.hpp"

using namespace Lurk::Network;
using ::testing::_;
using ::testing::Return;


TEST(TcpClientTest, inet_pton_test) {
	sockaddr_in sa;
	ASSERT_EQ(TcpClient::inet_pton(AF_INET,"127.0.0.1",&sa),1);
}

TEST(TcpClientTest, ConnectToServer_test) {
	MockSocket* mock = new MockSocket();
	auto client = TcpClient(std::unique_ptr<MockSocket>(mock));

	ASSERT_EQ(client.ConnectToServer("malaurydu", 2000), TcpExceptions::InvalidAddress);

	EXPECT_CALL(*mock, Connect(_, _))
		.Times(1)
		.WillOnce(Return(-1));

	ASSERT_EQ(client.ConnectToServer("127.0.0.1", 2000), TcpExceptions::ConnectionError);
	
	EXPECT_CALL(*mock, Connect(_, _))
		.Times(1)
		.WillOnce(Return(1));

	ASSERT_EQ(client.ConnectToServer("127.0.0.1", 2000), TcpExceptions::NoException);

}