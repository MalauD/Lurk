#pragma once
#include "gtest/gtest.h"
#include "./../../Src/Event/Event.hpp"
#include "./../../Src/Event/ServerEvents/ServerEventTypes.hpp"
#include "./../../Src/Event/ServerEvents/ServerEventArgs.hpp"

using namespace Lurk::Event;


TEST(EventTest,Subscribe_test) {
	Event<ServerEventTypes, int> myEvent;

	ASSERT_FALSE((bool)myEvent.GetFunc());

	myEvent.Subscribe([&](EventArgs<ServerEventTypes, int> args) {
			ASSERT_TRUE(false);
		});

	ASSERT_TRUE((bool)myEvent.GetFunc());

			
}

TEST(EventTest,UnSubscribe_test) {
	Event<ServerEventTypes, int> myEvent;

	myEvent.Subscribe([&](EventArgs<ServerEventTypes, int> args) {
			ASSERT_TRUE(false);
		});

	myEvent.UnSubscribe();

	ASSERT_FALSE((bool)myEvent.GetFunc());
}

TEST(EventTest,GetFunc_test) {
	ASSERT_TRUE(true);
}

TEST(EventTest,CallTest) {
	Event<ServerEventTypes, int> myEvent;

	myEvent.Subscribe([&](EventArgs<ServerEventTypes, int> args) {
			ASSERT_EQ(args.GetArg(), 20);
			ASSERT_EQ((int)args.GetType(), 0);
		});

	auto args = ServerEventArgs<int>(ServerEventTypes::OnNewClient,20);

	myEvent.Call(args);
}

