#include "asset/rShaderManager.hpp"

rShaderManager::rShaderManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rAssetManager<rShader, rShaderData, rShaderFile>(fileSystem)
{
	m_graphicsDevice = graphicsDevice;
}

rShader* rShaderManager::CreateAssetFromData(const rShaderData& shaderData, const rString& name) {
	unsigned int shaderId = m_graphicsDevice->CreateShaderProgram(shaderData.VertexProgram(), shaderData.FragmentProgram());

	return new rShader(name, shaderId);
}

void rShaderManager::DisposeAsset(rShader* shader) {
	m_graphicsDevice->DeleteShaderProgram(shader->ProgramId());
}

rShader* rShaderManager::DefaultModelShader(){
	return Retain("default_model");
}

rShader* rShaderManager::DefaultLineShader(){
	return Retain("default_colored");
}

rShader* rShaderManager::DefaultPrimitiveShader(){
	return Retain("default_primitive");
}

rShader* rShaderManager::DefaultSpriteShader() {
	return Retain("default_sprite");
}