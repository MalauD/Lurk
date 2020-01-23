#pragma once
#include "gtest/gtest.h"
#include "./../../Src/Event/Event.hpp"
#include "./../../Src/Event/EventArgs.hpp"

using namespace Lurk;

class TestEventArgs : Lurk::Event::EventArgs{
	public:
		TestEventArgs(int A) : a(A) {}
		int a;
};

TEST(EventTest,Subscribe_test) {
	Event::Event<TestEventArgs> myEvent;

	ASSERT_FALSE(myEvent.IsCallable());

	myEvent.Subscribe([&](TestEventArgs args) {
			ASSERT_TRUE(false);
		});

	ASSERT_TRUE(myEvent.IsCallable());

	myEvent.UnSubscribe();

	myEvent += [&](TestEventArgs args) {
		ASSERT_TRUE(false);
	};

	ASSERT_TRUE(myEvent.IsCallable());
}

TEST(EventTest,UnSubscribe_test) {
	Event::Event<TestEventArgs> myEvent;

	myEvent.Subscribe([&](TestEventArgs args) {
			ASSERT_TRUE(false);
		});

	myEvent.UnSubscribe();

	ASSERT_FALSE(myEvent.IsCallable());
}

TEST(EventTest,GetFunc_test) {
	ASSERT_TRUE(true);
}

TEST(EventTest,CallTest) {
	Event::Event<TestEventArgs> myEvent;

	myEvent.Subscribe([&](TestEventArgs args) {
			ASSERT_EQ(args.a, 20);
		});

	auto args = TestEventArgs(20);

	myEvent.Call(args);
}

TEST(EventTest, GetSubscribedFuncsLength_test) {
	Event::Event<TestEventArgs> myEvent;

	myEvent.Subscribe([&](TestEventArgs args) {
			testing::AssertionFailure();
		});

	myEvent.Subscribe([&](TestEventArgs args) {
			testing::AssertionFailure();
		});

	ASSERT_EQ(myEvent.GetSubscribedFuncsLength(), 2);
}

TEST(EventTest, IsCallable_test) {
	Event::Event<TestEventArgs> myEvent;

	ASSERT_FALSE(myEvent.IsCallable());

	myEvent.Subscribe([&](TestEventArgs args) {
		testing::AssertionFailure();
		});

	ASSERT_TRUE(myEvent.IsCallable());
}