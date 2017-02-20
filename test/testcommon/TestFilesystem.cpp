#include "TestFilesystem.hpp"

rIStream* TestFilesystem::OpenReadFileRef(const rString& path) {
	rIStringStream* stream = nullptr;

	if (savedData.count(path)) {
		stream = new rIStringStream(savedData[path]);
	}
	else {
		stream = new rIStringStream();
	}

	return stream;
}

void TestFilesystem::CloseReadFileRef(rIStream* stream) {
	delete stream;
}

rOStream* TestFilesystem::OpenWriteFileRef(const rString& path) {
	rOStringStream* stream = new rOStringStream();
	openWriteableFiles[stream] = path;

	return stream;
}

void TestFilesystem::CloseWriteFileRef(rOStream* stream) {
	rOStringStream* stringstream = (rOStringStream*)stream;

	rString str = stringstream->Str();
	rString path = openWriteableFiles[stringstream];

	savedData[path] = str;
	openWriteableFiles.erase(stringstream);

	delete stream;
}

void TestFilesystem::SetSavedSata(const rString& path, const rString& data) {
	savedData[path] = data;
}

void TestFilesystem::Clear() {
	for (auto& item : openReadableFiles)
		delete item;

	for (auto& item : openWriteableFiles)
		delete item.first;

	savedData.clear();
}

TestFilesystem::~TestFilesystem() {
	Clear();
}

bool TestFilesystem::FileSize(const rString& path, size_t& size) const {
	auto result = savedData.find(path);

	if (result == savedData.end()) {
		return false;
	}
	else {
		size = result->second.size();
		return true;
	}
}

bool TestFilesystem::Exists(const rString& path) {
	return savedData.count(path) > 0;
}