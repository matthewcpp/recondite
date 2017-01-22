#include "rgl/rOpenGLContentManager.hpp"
#include "rPath.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem, iResourceManager* resourceManager)
	:rContentManager(graphicsDevice, fileSystem, resourceManager)
{}

bool rOpenGLContentManager::InitDefaultAssets(const rString& defaultAssetPath){
	Log::Info("Loading Default OpengGL Shaders");

	rShaderManager* shaderManager = Shaders();
	rShader* shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_sprite__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_text__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_drawing__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_primitive__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_model__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_line__");
	if (!shader) return false;

	shader = shaderManager->LoadFromPath(defaultAssetPath, "__default_skinned__");
	if (!shader) return false;

	rString defaultFontPath = rPath::Combine(defaultAssetPath, "__default_font__.rfnt");
	Font::Family* font = Fonts()->LoadFromPath(defaultFontPath, "__default_font__");
	if(!font) return false;

	return true;
}