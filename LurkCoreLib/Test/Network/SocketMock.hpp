#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./../../Src/Network/Socket.hpp"

using namespace Lurk;

class MockSocket : public Network::Socket {
	public:
		MOCK_METHOD2(Bind, int(const sockaddr*, socklen_t));
		MOCK_METHOD1(Listen, int(int));
		MOCK_METHOD2(Accept, Socket*(sockaddr*, socklen_t));
		MOCK_METHOD2(Connect, int(const sockaddr*, socklen_t));
		MOCK_METHOD3(Send, int(const void*, int, int));
		MOCK_METHOD3(Recv, int(const void*, int, int));
		MOCK_METHOD0(IsAlive, bool());
		MockSocket(int i) { _socket = i; }
		MockSocket() = default;
		~MockSocket() = default;
};