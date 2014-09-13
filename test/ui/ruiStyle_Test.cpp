#include "gtest/gtest.h"

#include "ui/ruiStyle.hpp"

class Ui_ruiStyle : public ::testing::Test{};

TEST(Ui_ruiStyle, Extend){
	ruiStyle baseStyle;
	rTexture2D* testTexture1 = new rTexture2D(0,0,3,0,0,"test1","/test/rtex1");
	rTexture2D* testTexture2 = new rTexture2D(0,0,3,0,0,"test2","/test/rtex2");

	float floatVal = 5566.2187f;
	int intVal = 8675309;

	bool b; int i; float f; rTexture2D* tex;

	ruiStyle style1;
	style1.SetBool("bool", true);
	style1.SetTexture("texture", testTexture1);
	style1.SetFloat("float", floatVal);

	ruiStyle style2;
	style2.SetBool("bool", false);
	style2.SetTexture("texture", testTexture2);
	style2.SetInt("int", intVal);

	baseStyle.Extend(style1);
	
	ASSERT_EQ(baseStyle.NumProperties(), style1.NumProperties());

	ASSERT_TRUE(baseStyle.GetBool("bool", b));
	ASSERT_TRUE(b);

	ASSERT_TRUE(baseStyle.GetTexture("texture", tex));
	ASSERT_EQ(tex, testTexture1);

	ASSERT_TRUE(baseStyle.GetFloat("float", f));
	ASSERT_EQ(f, floatVal);

	baseStyle.Extend(style2);

	ASSERT_EQ(baseStyle.NumProperties(), 4);

	ASSERT_TRUE(baseStyle.GetBool("bool", b));
	ASSERT_FALSE(b);

	ASSERT_TRUE(baseStyle.GetTexture("texture", tex));
	ASSERT_EQ(tex, testTexture2);

	ASSERT_TRUE(baseStyle.GetInt("int", i));
	ASSERT_EQ(i, intVal);


	delete testTexture1;
	delete testTexture2;
}