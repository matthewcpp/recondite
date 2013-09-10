#ifndef R_ANDROIDDEMOAPP_HPP
#define R_ANDROIDDEMOAPP_HPP

#include "rAndroidApplication.hpp"

#include "data/rMaterialData.hpp"
#include "data/rTexture2DData.hpp"
#include "data/rGeometryData.hpp"

class rAndroidDemoApp : public rAndroidApplication{
public:
	rAndroidDemoApp();
	virtual void Draw();
	virtual bool Init(android_app* state);

private:
	void CreateGeometry();
	void CreateTextureMaterial();
	void CreateColoredShader(const char* name, const char* value);

	void DrawTextured();
	void DrawShaded();
	void DrawImmediate();

private:
	unsigned int m_frame;
};

#endif
