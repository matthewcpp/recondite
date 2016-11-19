#include "asset/rShaderManager.hpp"

#include <map>
#include <memory>
#include <functional>

#include "rPath.hpp"
#include "rDefs.hpp"



struct rShaderManager::Impl{
	rGraphicsDevice* graphicsDevice;
	rFileSystem* fileSystem;

	std::map<rString, std::unique_ptr<rShader>> shaders;

	Impl(rGraphicsDevice* _graphicsDevice, rFileSystem* _fileSystem) : graphicsDevice(_graphicsDevice), fileSystem(_fileSystem){}

	rShader* Create(const rString& vertex, const rString& fragment, const rString& name);
};

rShaderManager::rShaderManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
{
	_impl = new Impl(graphicsDevice, fileSystem);
}

rShaderManager::~rShaderManager(){
	delete _impl;
}

rShader* rShaderManager::LoadFromPath(const rString& directory, const rString& name){
	if (Get(name)) return nullptr;


	rString vertexShaderPath = rPath::Assemble(directory, name, "vert");
	rString fragmentShaderPath = rPath::Assemble(directory, name, "frag");

	auto vertexShaderFile = _impl->fileSystem->GetReadFileRef(vertexShaderPath);
	auto fragmentShaderFile = _impl->fileSystem->GetReadFileRef(fragmentShaderPath);

	if (vertexShaderFile && fragmentShaderFile){
		//read the files into strings
		vertexShaderFile->Seek(0, rSeekMode::End);
		size_t size = vertexShaderFile->Pos();
		vertexShaderFile->Seek(0, rSeekMode::Beginning);
		rString vertexShaderStr(size, ' ');
		vertexShaderFile->Read(&vertexShaderStr[0], size);

		fragmentShaderFile->Seek(0, rSeekMode::End);
		size = fragmentShaderFile->Pos();
		fragmentShaderFile->Seek(0, rSeekMode::Beginning);
		rString fragmentShaderStr(size, ' ');
		fragmentShaderFile->Read(&fragmentShaderStr[0], size);

		return _impl->Create(vertexShaderStr, fragmentShaderStr, name);
	}
	else{
		return nullptr;
	}
}

rShader* rShaderManager::Load(const rString& vertex, const rString& fragment, const rString& name){
	if (Get(name)){
		return nullptr;
	}
	else{
		return _impl->Create(vertex, fragment, name);
	}
}

rShader* rShaderManager::Impl::Create(const rString& vertex, const rString& fragment, const rString& name){
	unsigned int shaderId = graphicsDevice->CreateShaderProgram(vertex, fragment);

	if (shaderId > 0){
		rShader* shader = new rShader(name, shaderId);
		std::unique_ptr<rShader> ref(shader);
		shaders.insert(std::make_pair(name, std::move(ref)));
		return shader;
	}
	else{
		return nullptr;
	}

}

rShader* rShaderManager::Get(const rString& name){
	auto result = _impl->shaders.find(name);

	if (result == _impl->shaders.end()){
		return nullptr;
	}
	else{
		return result->second.get();
	}
}

int rShaderManager::Delete(const rString& name){
	auto result = _impl->shaders.find(name);

	if (result == _impl->shaders.end()){
		return 1;
	}
	
	_impl->graphicsDevice->DeleteShaderProgram(result->second.get()->ProgramId());
	_impl->shaders.erase(result);
	return 0;
}

void rShaderManager::Clear(){
	_impl->shaders.clear();
}

rShader* rShaderManager::DefaultModelShader(){
	return Get("__default_model__");
}

rShader* rShaderManager::DefaultLineShader(){
	return Get("__default_line__");
}

rShader* rShaderManager::DefaultPrimitiveShader(){
	return Get("__default_primitive__");
}

rShader* rShaderManager::DefaultSpriteShader() {
	return Get("__default_sprite__");
}

rShader* rShaderManager::DefaultTextShader(){
	return Get("__default_text__");
}

rShader* rShaderManager::DefaultDrawingShader(){
	return Get("__default_drawing__");
}

rShader* rShaderManager::DefaultSkinnedShader() {
	return Get("__default_skinned__");
}