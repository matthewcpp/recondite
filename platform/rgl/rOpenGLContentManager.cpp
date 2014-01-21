#include "rOpenGLContentManager.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice)
	:rContentManager(graphicsDevice)
{

}

void rOpenGLContentManager::InitDefaultAssets(){
	#include "rOpenGLDefaultShaders.inl"

    rShaderData shaderData;

    shaderData.SetShaderData(coloredVertexShader, coloredFragmentShader);
    rShader* result = LoadShader(shaderData, "default_colored");

    shaderData.SetShaderData(pointVertexShader, coloredFragmentShader);
	result = LoadShader(shaderData, "default_points");

    shaderData.SetShaderData(texturedVertexShader, texturedFragmentShader);
    result = LoadShader(shaderData, "default_textured");

    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
    materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");
	LoadMaterial(materialData, "default_colored");

	materialData.SetShader("default_points", "");
	materialData.SetParameter( rMATERIAL_PARAMETER_FLOAT , "recPointSize", "1");
	LoadMaterial(materialData, "default_points");
}