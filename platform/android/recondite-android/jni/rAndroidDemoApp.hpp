#ifndef R_ANDROIDDEMOAPP_HPP
#define R_ANDROIDDEMOAPP_HPP

#include "rAndroidApplication.hpp"

#include "data/rMaterialData.hpp"
#include "data/rTexture2DData.hpp"
#include "data/rGeometryData.hpp"

#include "ui/ruiDPad.hpp"
#include "ui/ruiPicker.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiLayoutManager.hpp"
#include "ui/ruiText.hpp"

#include "rEngine.hpp"

class rAndroidDemoApp : public rAndroidApplication{
public:
	rAndroidDemoApp();

	virtual bool Init(android_app* state);

	virtual void Update();
	virtual void Draw();

private:
	void CreateGeometry();
	void CreateTextureMaterial();
	void CreateColoredShader(const char* name, const char* value);

	void UpdateCamera();

	void DrawTextured();
	void DrawShaded();
	void DrawImmediate();

private:
	unsigned int m_frame;

	ruiLayoutManager* m_layoutManager;
	float rot;
};

#endif
