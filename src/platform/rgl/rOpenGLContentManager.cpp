#include "rgl/rOpenGLContentManager.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rContentManager(graphicsDevice, fileSystem)
{}

void rOpenGLContentManager::InitDefaultAssets(){
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
}