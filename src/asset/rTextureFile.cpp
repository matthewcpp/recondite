#include "asset/rTextureFile.hpp"

const int MagicNumber = 2019914866;

int ReadTextureHeader(rIStream& stream, rTextureData& textureData){
	return 0;
}

int ReadTextureData(rIStream& stream, rTextureData& textureData){
	return 0;
}

rContentError rTextureFile::Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rTextureData>& textureData){

	return rContentError::None;
}