#include "gtest/gtest.h"
#include "rTypes.hpp"
#include "rEventHandler.hpp"
#include "fakes/FakeEventListener.hpp"

bool global_bool_var = false;

void gloabl_event_func(rEvent& event){
	global_bool_var = true;
}

class Core_rEventHandler : public ::testing::Test{
};

TEST(Core_rEventHandler, BindEventCallbackWithTarget){
	int eventType = 55662187;
	FakeEventListener tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &FakeEventListener::EventCallback);
	eventHandler.Bind(eventType, &tester2, &FakeEventListener::EventCallback);

	eventHandler.Trigger(eventType, event);
	EXPECT_TRUE(tester1.CallbackCalled());
	EXPECT_TRUE(tester2.CallbackCalled());
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
	FakeEventListener tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType1, &tester1, &FakeEventListener::EventCallback);
	eventHandler.Bind(eventType2, &tester2, &FakeEventListener::EventCallback);

	eventHandler.Trigger(eventType1, event);
	EXPECT_TRUE(tester1.CallbackCalled());
	EXPECT_FALSE(tester2.CallbackCalled());

	tester1.Reset();
	tester2.Reset();

	eventHandler.Trigger(eventType2, event);
	EXPECT_FALSE(tester1.CallbackCalled());
	EXPECT_TRUE(tester2.CallbackCalled());
}

TEST(Core_rEventHandler, StopsPropagationWhenHandled){
	int eventType = 55662187;
	FakeEventListener tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &FakeEventListener::HandleCallback);
	eventHandler.Bind(eventType, &tester1, &FakeEventListener::EventCallback);

	eventHandler.Trigger(eventType, event);
	EXPECT_TRUE(tester1.CallbackCalled());
	EXPECT_FALSE(tester2.CallbackCalled());
}

TEST(Core_rEventHandler, UnbindEventCallbackWithGlobal){
	int eventType = 55662187;
	FakeEventListener tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &FakeEventListener::EventCallback);
	eventHandler.Bind(eventType, &tester2, &FakeEventListener::EventCallback);

	eventHandler.Unbind(eventType, &tester1, &FakeEventListener::EventCallback);

	eventHandler.Trigger(eventType, event);
	EXPECT_FALSE(tester1.CallbackCalled());
	EXPECT_TRUE(tester2.CallbackCalled());
}

TEST(Core_rEventHandler, UnbindEventCallbackWithTarget){
	int eventType = 55662187;
	FakeEventListener tester1, tester2;
	rEventHandler eventHandler;
	rEvent event;

	eventHandler.Bind(eventType, &tester1, &FakeEventListener::EventCallback);
	eventHandler.Bind(eventType, &tester2, &FakeEventListener::EventCallback);

	eventHandler.Unbind(eventType, &tester1, &FakeEventListener::EventCallback);

	eventHandler.Trigger(eventType, event);
	EXPECT_FALSE(tester1.CallbackCalled());
	EXPECT_TRUE(tester2.CallbackCalled());
}

TEST(Core_rEventHandler, TriggersUnboundEventOk){
	rEventHandler eventHandler;
	rEvent event;

	EXPECT_NO_THROW( eventHandler.Trigger(99, event) );
}