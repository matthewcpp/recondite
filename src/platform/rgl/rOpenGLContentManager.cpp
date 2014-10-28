#include "rgl/rOpenGLContentManager.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice)
	:rContentManager(graphicsDevice)
{

}

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

    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
    materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");
	LoadMaterial(materialData, "default_colored");

	materialData.SetShader("default_points", "");
	materialData.SetParameter( rMATERIAL_PARAMETER_FLOAT , "recPointSize", "1");
	LoadMaterial(materialData, "default_points");
}