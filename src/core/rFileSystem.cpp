#include "rFileSystem.hpp"

rFileSystem::rIStreamRef rFileSystem::GetReadFileRef(const rString& path){
	rIStreamRef fileStream;
	fileStream.reset(new rIFileStream(path));

	if (!fileStream->IsOk()){
		fileStream.reset();
	}

	return fileStream;
}

rFileSystem::rOStreamRef rFileSystem::GetWriteFileRef(const rString& path){
	rOStreamRef fileStream;
	fileStream.reset(new rOFileStream(path));

	if (!fileStream->IsOk()){
		fileStream.reset();
	}

	return fileStream;
}