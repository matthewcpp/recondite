#include "gtest/gtest.h"

#include "ui/ruiCheckbox.hpp"
#include "fakes/FakeEventListener.hpp"

class Ui_ruiCheckbox : public ::testing::Test{};

TEST(Ui_ruiCheckbox, TriggersCheckboxEventWhenClicked){
	FakeEventListener callbackTester;
	ruiCheckbox checkbox("checkbox", NULL, rPoint(0,0), rSize(50,50));
	checkbox.Bind(ruiEVENT_CHECKBOX_CHANGE, &callbackTester, &FakeEventListener::EventCallback);

	ruiMouseEvent event1(rMOUSE_BUTTON_LEFT, rBUTTON_STATE_DOWN, rPoint(20,20));
	checkbox.Trigger(ruiEVT_MOUSE_UP, event1);

	EXPECT_TRUE(callbackTester.CallbackCalled());
}