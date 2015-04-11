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

	shaderData.SetShaderData(vertexColorVertexShader, vertexColorFragmentShader);
	result = LoadShader(shaderData, "default_vertex_color_geometry");

    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
	materialData.SetParameter(rPROPERTY_TYPE_COLOR, "fragColor", "255 255 255 255");
	LoadMaterial(materialData, "default_colored");

	materialData.SetShader("default_points", "");
	materialData.SetParameter(rPROPERTY_TYPE_FLOAT, "recPointSize", "1");
	LoadMaterial(materialData, "default_points");

	materialData.Clear();
	materialData.SetShader("default_vertex_color_geometry", "");
	LoadMaterial(materialData, "default_vertex_color_geometry");
}