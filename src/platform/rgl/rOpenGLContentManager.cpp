#include "rgl/rOpenGLContentManager.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice)
	:rContentManager(graphicsDevice)
{}

void rOpenGLContentManager::InitDefaultAssets(){
	#include "rgl/rOpenGLDefaultShaders.inl"
	rLog::Info("Loading OpengGL Shaders");

    rShaderData shaderData;

    shaderData.SetShaderData(coloredVertexShader, coloredFragmentShader);
    rShader* result = LoadShader(shaderData, "default_colored");

    shaderData.SetShaderData(pointVertexShader, coloredFragmentShader);
	result = LoadShader(shaderData, "default_points");

    shaderData.SetShaderData(texturedVertexShader, texturedFragmentShader);
    result = LoadShader(shaderData, "default_textured");

	shaderData.SetShaderData(modelVertexShader, texturedFragmentShader);
    result = LoadShader(shaderData, "default_model");

	shaderData.SetShaderData(coloredVertexShader, vertexColorFragmentShader);
	result = LoadShader(shaderData, "default_vertex_color_geometry");
}