#include "reProjectResourceManager.hpp"

reProjectResourceManager::reProjectResourceManager() {
	_project = nullptr;
}

void reProjectResourceManager::SetProject(reProject* project) {
	_project = project;
}

rIStream* reProjectResourceManager::Open(const rString& handle) {
	if (_project == nullptr || !_project->IsOpen()) return nullptr;

	rIFileStream* result = nullptr;
	wxFileName resourcePath(_project->Assets()->GetDirectoryPath() + handle.c_str());

	if (resourcePath.Exists()) {
		result = new rIFileStream(resourcePath.GetFullPath().c_str().AsChar());
	}
	else {
		resourcePath = _project->Directory() + '/' + handle.c_str();

		if (resourcePath.Exists()) {
			result = new rIFileStream(resourcePath.GetFullPath().c_str().AsChar());
		}
	}

	return result;
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