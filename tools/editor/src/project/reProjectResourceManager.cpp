#include "reProjectResourceManager.hpp"

reProjectResourceManager::reProjectResourceManager(reProject* project) {
	_project = project;
}

rIStream* reProjectResourceManager::Open(const rString& handle) {
	if (!_project->IsOpen()) return nullptr;

	wxFileName resourcePath(_project->Assets()->GetDirectoryPath() + handle.c_str());

	if (resourcePath.Exists()) {
		return new rIFileStream(resourcePath.GetFullPath().c_str().AsChar());
	}
	else {
		return nullptr;
	}
}

bool reProjectResourceManager::Close(rIStream* stream) {
	if (_openHandles.count(stream)) {
		_openHandles.erase(stream);
		delete stream;

		return true;
	}
	else {
		return false;
	}
}