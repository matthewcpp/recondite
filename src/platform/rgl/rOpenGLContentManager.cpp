#include "rgl/rOpenGLContentManager.hpp"
#include "rPath.hpp"

rOpenGLContentManager::rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rContentManager(graphicsDevice, fileSystem)
{}

void rOpenGLContentManager::InitDefaultAssets(const rString& defaultAssetPath){
	rLog::Info("Loading Default OpengGL Shaders");

	rShaderManager* shaderManager = Shaders();
	shaderManager->LoadFromPath(defaultAssetPath, "__default_sprite__");
	shaderManager->LoadFromPath(defaultAssetPath, "__default_text__");
	shaderManager->LoadFromPath(defaultAssetPath, "__default_drawing__");
	shaderManager->LoadFromPath(defaultAssetPath, "__default_primitive__");

	rString defaultFontPath = rPath::Combine(defaultAssetPath, "__default_font__.rfnt");
	Fonts()->LoadFromPath(defaultFontPath, "__default_font__");
}