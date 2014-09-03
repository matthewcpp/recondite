#include "gtest/gtest.h"
#include "rTypes.hpp"
#include "rEventHandler.hpp"

bool global_bool_var = false;

void gloabl_event_func(rEvent& event){
	global_bool_var = true;
}

class Core_rEventHandler : public ::testing::Test{
};

class TargetTester{
public:
	TargetTester() : callbackCalled(false){}
	void Callback(rEvent& event) {callbackCalled = true;}
	void HandleCallback(rEvent& event) {event.SetHandled();callbackCalled = true;}
	void Reset(){callbackCalled = false;}

	bool callbackCalled;
};

TEST(Core_rEventHandler, BindEventCallbackWithTarget){
	int eventType = 55662187;
	TargetTester tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &TargetTester::Callback);
	eventHandler.Bind(eventType, &tester2, &TargetTester::Callback);

	eventHandler.Trigger(eventType, event);
	EXPECT_TRUE(tester1.callbackCalled);
	EXPECT_TRUE(tester2.callbackCalled);
}

TEST(Core_rEventHandler, BindEventCallbackWithGlobal){
	global_bool_var = false;
	int eventType = 55662187;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &gloabl_event_func);
	eventHandler.Trigger(eventType, event);

	EXPECT_TRUE(global_bool_var);
}

TEST(Core_rEventHandler, FiresCorrectCallbacksForEvent){
	int eventType1 = 55662187;
	int eventType2 = 5566;
	TargetTester tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType1, &tester1, &TargetTester::Callback);
	eventHandler.Bind(eventType2, &tester2, &TargetTester::Callback);

	eventHandler.Trigger(eventType1, event);
	EXPECT_TRUE(tester1.callbackCalled);
	EXPECT_FALSE(tester2.callbackCalled);

	tester1.Reset();
	tester2.Reset();

	eventHandler.Trigger(eventType2, event);
	EXPECT_FALSE(tester1.callbackCalled);
	EXPECT_TRUE(tester2.callbackCalled);
}

TEST(Core_rEventHandler, StopsPropagationWhenHandled){
	int eventType = 55662187;
	TargetTester tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &TargetTester::HandleCallback);
	eventHandler.Bind(eventType, &tester1, &TargetTester::Callback);

	eventHandler.Trigger(eventType, event);
	EXPECT_TRUE(tester1.callbackCalled);
	EXPECT_FALSE(tester2.callbackCalled);
}

TEST(Core_rEventHandler, UnbindEventCallbackWithGlobal){
	int eventType = 55662187;
	TargetTester tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &TargetTester::Callback);
	eventHandler.Bind(eventType, &tester2, &TargetTester::Callback);

	eventHandler.Unbind(eventType, &tester1, &TargetTester::Callback);

	eventHandler.Trigger(eventType, event);
	EXPECT_FALSE(tester1.callbackCalled);
	EXPECT_TRUE(tester2.callbackCalled);
}

TEST(Core_rEventHandler, UnbindEventCallbackWithTarget){
	int eventType = 55662187;
	TargetTester tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &TargetTester::Callback);
	eventHandler.Bind(eventType, &tester2, &TargetTester::Callback);

	eventHandler.Unbind(eventType, &tester1, &TargetTester::Callback);

	eventHandler.Trigger(eventType, event);
	EXPECT_FALSE(tester1.callbackCalled);
	EXPECT_TRUE(tester2.callbackCalled);
}