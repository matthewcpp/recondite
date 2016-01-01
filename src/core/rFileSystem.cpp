#include "rFileSystem.hpp"

rFileSystem::rIFileStreamHandle rFileSystem::GetReadFileRef(const rString& path){
	rIFileStreamHandle fileStream;
	fileStream.reset(new rIFileStream(path));

	if (!fileStream->IsOk()){
		fileStream.reset();
	}

	return fileStream;
}

rFileSystem::rOFileStreamHandle rFileSystem::GetWriteFileRef(const rString& path){
	rOFileStreamHandle fileStream;
	fileStream.reset(new rOFileStream(path));

	if (!fileStream->IsOk()){
		fileStream.reset();
	}

	return fileStream;
}