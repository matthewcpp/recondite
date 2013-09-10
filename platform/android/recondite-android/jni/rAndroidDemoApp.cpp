#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
}

void rAndroidDemoApp::Draw(){
	if (m_started){
		m_graphicsDevice->Clear();
		m_renderer->Render(m_viewport);

		DrawTextured();
		DrawShaded();
		DrawImmediate();

		m_graphicsDevice->SwapBuffers();
		m_frame++;
	}
}

bool rAndroidDemoApp::Init(android_app* state){
	bool result = rAndroidApplication::Init(state);

	if (result){
		rLog::Info("Init demo assets");
		CreateGeometry();
		CreateTextureMaterial();
		CreateColoredShader("red_shaded", "255 0 0 255");
		CreateColoredShader("green_shaded", "0 255 0 255");
	}

	return result;
}

void rAndroidDemoApp::CreateColoredShader(const char* name, const char* value){
    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
    materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", value);

    m_contentManager->LoadMaterial(materialData, name);
}

void rAndroidDemoApp::CreateTextureMaterial(){
	   unsigned char pixels[] = {
		  128,   92,   61, // brown
			191, 27,   224, // purple
			0,   0, 255, // Blue
		  255, 255,   0	// Yellow
	   };


	   rTexture2DData texture;
	   texture.SetImageData(2,2,3,pixels);
	   rTexture2D* t = m_contentManager->LoadTexture(texture, "texture");

	   rMaterialData materialData;
	   materialData.SetShader("default_textured", "");
	   materialData.SetParameter( rMATERIAL_PARAMETER_TEXTURE2D , "s_texture", "texture");

	   m_contentManager->LoadMaterial(materialData, "test_tex");
}

void rAndroidDemoApp::CreateGeometry(){
	float verts[] = { 	-0.5f,  0.5f, 0.0f,  // Position 0
						-0.5f, -0.5f, 0.0f,  // Position 1
						 0.5f, -0.5f, 0.0f,  // Position 2
						 0.5f,  0.5f, 0.0f,  // Position 3
					  };

	float tex_verts[] = { 	-0.5f,  0.5f, 0.0f,  // Position 0
	                         0.0f,  0.0f,        // TexCoord 0
	                         -0.5f, -0.5f, 0.0f,  // Position 1
	                         0.0f,  1.0f,        // TexCoord 1
	                         0.5f, -0.5f, 0.0f,  // Position 2
	                         1.0f,  1.0f,        // TexCoord 2
	                         0.5f,  0.5f, 0.0f,  // Position 3
	                         1.0f,  0.0f         // TexCoord 3
	                      };

	unsigned short elements[] = { 0, 1, 2, 0, 2, 3 };

		rGeometryData data;
		data.SetVertexData(verts, 3, 4, false, false);
		data.CreateElementBuffer("rect",elements, 6);
		m_contentManager->LoadGeometry(data, "rect");

		data.SetVertexData(tex_verts, 3, 4, true, false);
		m_contentManager->LoadGeometry(data, "texture_rect");
}

void rAndroidDemoApp::DrawTextured(){
	rMatrix4 matrix;
	matrix.SetTranslate(-1.0f, 0.0f, 0.0f);
	rGeometry* geometry = m_contentManager->GetGeometryAsset("texture_rect");
	rMaterial* material = m_contentManager->GetMaterialAsset("test_tex");
	m_renderer->RenderGeometry(geometry, matrix, "rect", material);
}

void rAndroidDemoApp::DrawShaded(){
	rMatrix4 matrix;
	matrix.SetTranslate(1.0f,0,0);
	rGeometry* geometry = m_contentManager->GetGeometryAsset("rect");
	rMaterial* material = (m_frame % 120 < 60) ?
		m_contentManager->GetMaterialAsset("red_shaded") :
		m_contentManager->GetMaterialAsset("green_shaded");

	m_renderer->RenderGeometry(geometry, matrix, "rect", material);
}

void rAndroidDemoApp::DrawImmediate(){
	rRect square(100,100, 200,200);
	rColor purple(160,32,240, 255);

	m_renderer->RenderRect(square,purple);
}
