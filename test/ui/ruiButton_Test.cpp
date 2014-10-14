#include "gtest/gtest.h"

#include "ui/ruiButton.hpp"
#include "fakes/FakeEventListener.hpp"

class Ui_ruiButton : public ::testing::Test{};


TEST(Ui_ruiButton, SetsButtonStateOnLeftDown){
	ruiButton button("test", "test", NULL);

	EXPECT_EQ(rBUTTON_STATE_UP, button.ButtonState());

	ruiMouseEvent event(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(20,20));
	button.Trigger(ruiEVT_MOUSE_DOWN, event);

	EXPECT_EQ(rBUTTON_STATE_DOWN, button.ButtonState());
}

TEST(Ui_ruiButton, SetsButtonStateOnLeftUp){
	ruiButton button("test", "test", NULL);

	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(20,20));
	button.Trigger(ruiEVT_MOUSE_DOWN, event1);
	button.Trigger(ruiEVT_MOUSE_UP, event1);

	EXPECT_EQ(rBUTTON_STATE_UP, button.ButtonState());
}

TEST(Ui_ruiButton, TriggersButtonClickEventWhenClicked){
	FakeEventListener callbackTester;
	ruiButton button("test", "test", NULL);
	button.Bind(ruiEVENT_BUTTON_CLICK, &callbackTester, &FakeEventListener::EventCallback);

	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(20,20));
	button.Trigger(ruiEVT_MOUSE_DOWN, event1);
	button.Trigger(ruiEVT_MOUSE_UP, event1);

	EXPECT_TRUE(callbackTester.CallbackCalled());
}

TEST(Ui_ruiButton, DoesNotTriggerEventWhenMouseUpOutsideButton){
	FakeEventListener callbackTester;
	ruiButton button("test", "test", NULL);
	button.Bind(ruiEVENT_BUTTON_CLICK, &callbackTester, &FakeEventListener::EventCallback);

	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(20,20));
	button.Trigger(ruiEVT_MOUSE_DOWN, event1);

	ruiMouseEvent event2(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(100,20));
	button.Trigger(ruiEVT_MOUSE_UP, event2);

	EXPECT_FALSE(callbackTester.CallbackCalled());
}