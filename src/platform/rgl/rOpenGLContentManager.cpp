#include "rgl/rOpenGLContentManager.hpp"
#include "rPath.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rContentManager(graphicsDevice, fileSystem)
{}

void rOpenGLContentManager::InitDefaultAssets(const rString& defaultAssetPath){
	
	/*
    rShaderData shaderData;

    shaderData.Set(coloredVertexShader, coloredFragmentShader);
    rShader* result = shaderManager->LoadFromData(shaderData, "default_colored");

    shaderData.Set(pointVertexShader, coloredFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_points");

    shaderData.Set(texturedVertexShader, texturedFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_textured");

	shaderData.Set(coloredVertexShader, vertexColorFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_vertex_color_geometry");

	*/

	rLog::Info("Loading Default OpengGL Shaders");
	rShaderManager* shaderManager = Shaders();
	shaderManager->LoadFromPath(defaultAssetPath, "__default_sprite__");
	shaderManager->LoadFromPath(defaultAssetPath, "__default_text__");

	rString defaultFontPath = rPath::Combine(defaultAssetPath, "__default_font__.rfnt");
	Fonts()->LoadFromPath(defaultFontPath, "__default_font__");
}