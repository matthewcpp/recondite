#include "gtest/gtest.h"

#include "ui/ruiCheckbox.hpp"
#include "fakes/FakeEventListener.hpp"

class Ui_ruiCheckbox : public ::testing::Test{};

TEST(Ui_ruiCheckbox, TriggersCheckboxEventWhenClicked){
	FakeEventListener callbackTester;
	ruiCheckbox checkbox("checkbox", nullptr, nullptr);
	checkbox.Bind(ruiEVENT_CHECKBOX_CHANGE, &callbackTester, &FakeEventListener::EventCallback);

	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_UP, rPoint(20,20));
	checkbox.Trigger(ruiEVT_MOUSE_UP, event1);

	EXPECT_TRUE(callbackTester.CallbackCalled());
}

TEST(Ui_ruiCheckbox, SetsMouseEventEventToHandledIfClicked){
	ruiCheckbox checkbox("checkbox", nullptr, nullptr);
	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_UP, rPoint(20,20));
	ruiMouseEvent event2(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_UP, rPoint(600,20));

	checkbox.Trigger(ruiEVT_MOUSE_UP, event1);
	checkbox.Trigger(ruiEVT_MOUSE_UP, event2);

	EXPECT_TRUE(event1.Handled());
	EXPECT_FALSE(event2.Handled());
}