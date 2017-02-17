#include "rFileSystem.hpp"

rFileSystem::rIFileStreamHandle rFileSystem::GetReadFileRef(const rString& path){
	rIFileStreamHandle fileStream;
	fileStream.reset(OpenReadFileRef(path));
	return fileStream;
}

rIStream* rFileSystem::OpenReadFileRef(const rString& path) {
	rIStream* fileRef = new rIFileStream(path);

	if (fileRef->IsOk()) {
		return fileRef;
	}
	else {
		delete fileRef;
		return nullptr;
	}
}

void rFileSystem::CloseReadFileRef(rIStream* stream) {

}

rFileSystem::rOFileStreamHandle rFileSystem::GetWriteFileRef(const rString& path){
	rOFileStreamHandle fileStream;
	fileStream.reset(new rOFileStream(path));

	if (!fileStream->IsOk()){
		fileStream.reset();
	}

	return fileStream;
}