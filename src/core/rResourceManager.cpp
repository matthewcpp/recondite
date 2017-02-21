#include "rResourceManager.hpp"

#include <set>
#include <vector>
#include <memory>

#include "rArchive.hpp"

namespace recondite {
	struct ResourceManager::Impl {
		rString basePath;
		std::set<rIStream*> openHandles;
		std::vector<std::unique_ptr<Archive>> archives;
		rFileSystem* fileSystem;
	};

	ResourceManager::ResourceManager(rFileSystem* fileSystem) {
		_impl = new Impl();
		_impl->fileSystem = fileSystem;
	}

	ResourceManager::~ResourceManager() {
		delete _impl;
	}

	void ResourceManager::SetFilesystemBasePath(const rString& basePath) {
		_impl->basePath = basePath;
	}

	rIStream* ResourceManager::Open(const rString& handle) {
		rIStream* archiveFile = nullptr;

		for (auto& archive : _impl->archives) {
			archiveFile = archive->OpenStream(handle);
			if (archiveFile) break;
		}

		return archiveFile;
	}

	bool ResourceManager::Close(rIStream* stream) {
		return false;
	}

	bool ResourceManager::OpenArchive(const rString& path) {
		recondite::Archive* archive = new recondite::Archive(_impl->fileSystem);

		if (archive->LoadFromFilesystem(path)) {
			_impl->archives.emplace_back(archive);
			return true;
		}
		else {
			delete archive;
			return false;
		}
	}
}
