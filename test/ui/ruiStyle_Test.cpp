#include "gtest/gtest.h"

#include "ui/ruiStyle.hpp"

class Ui_ruiStyle : public ::testing::Test{};

TEST(Ui_ruiStyle, Clear){
	ruiStyle style;

	style.SetBool("bool", true);
	style.SetFloat("float", 3.14);
	style.SetInt("int", 55662187);

	ASSERT_EQ(style.NumProperties(), 3);

	style.Clear();

	ASSERT_EQ(style.NumProperties(), 0);
}

TEST(Ui_ruiStyle, Extend){
	ruiStyle baseStyle;
	rTexture* testTexture1 = new rTexture("test1", 64, 64, 3, 1);
	rTexture* testTexture2 = new rTexture("test2", 64, 64, 3, 2);

	float floatVal = 5566.2187f;
	int intVal = 8675309;

	bool b; int i; float f; rTexture* tex;

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