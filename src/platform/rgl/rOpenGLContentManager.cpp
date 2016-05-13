#include "rgl/rOpenGLContentManager.hpp"
#include "rPath.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rContentManager(graphicsDevice, fileSystem)
{}

void rOpenGLContentManager::InitDefaultAssets(const rString& defaultAssetPath){
	#include "rgl/rOpenGLDefaultShaders.inl"
	rLog::Info("Loading OpengGL Shaders");
	rShaderManager* shaderManager = Shaders();

    rShaderData shaderData;

    shaderData.Set(coloredVertexShader, coloredFragmentShader);
    rShader* result = shaderManager->LoadFromData(shaderData, "default_colored");

    shaderData.Set(pointVertexShader, coloredFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_points");

    shaderData.Set(texturedVertexShader, texturedFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_textured");

	shaderData.Set(modelVertexShader, texturedFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_model");

	shaderData.Set(coloredVertexShader, vertexColorFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_vertex_color_geometry");

	shaderData.Set(spriteVertexShader, spriteFragmentShader);
	result = shaderManager->LoadFromData(shaderData, "default_sprite");

	rString defaultFontPath = rPath::Combine(defaultAssetPath, "__default_font__.rfnt");
	Fonts()->LoadFromPath(defaultFontPath, "__default_font__");
}