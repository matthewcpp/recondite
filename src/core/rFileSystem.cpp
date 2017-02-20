#include "rFileSystem.hpp"

#include "stream/rIFileStream.hpp"
#include "stream/rOFileStream.hpp"

#ifdef _MSC_VER
	#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
#endif


rIStream* rFileSystem::OpenReadFileRef(const rString& path) {
	if (Exists(path)) {
		return new rIFileStream(path);
	}
	else {
		return nullptr;
	}
}

void rFileSystem::CloseReadFileRef(rIStream* stream) {
	delete stream;
}

rOStream* rFileSystem::OpenWriteFileRef(const rString& path) {
	if (Exists(path)) {
		return new rOFileStream(path);
	}
	else {
		return nullptr;
	}
}

void rFileSystem::CloseWriteFileRef(rOStream* stream) {
	delete stream;
}

bool rFileSystem::Exists(const rString& path) {
	fs::path fsPath(path.c_str());
	return fs::exists(fsPath);
}

bool rFileSystem::FileSize(const rString& path, size_t& size) const {
	fs::path fsPath(path.c_str());
	bool result = false;

	try {
		size = (size_t)fs::file_size(fsPath);
		result = true;
	}
	catch (fs::filesystem_error& e) {
		result = false;
	}

	return result;
}