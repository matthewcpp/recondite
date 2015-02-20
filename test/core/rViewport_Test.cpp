#include "gtest/gtest.h"
#include "rViewport.hpp"
#include "rCamera.hpp"

class Core_rViewport : public ::testing::Test{
};

TEST(Core_rViewport, GetViewFrustrum){
	rCamera camera("test", NULL);
	camera.SetRotation(rVector3(0,180,0));
	rViewport viewport("test");
	viewport.SetScreenRect(0,0,640,480);
	viewport.SetCamera(&camera);
	rFrustrum f;
	viewport.GetViewFrustrum(f);

	EXPECT_TRUE(!f.PointInFrustrum(rVector3(0,0,-5)));
	EXPECT_FALSE(!f.PointInFrustrum(rVector3(0,0,5)));
}