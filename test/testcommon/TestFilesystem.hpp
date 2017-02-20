#pragma once

#include <map>
#include <set>

#include "rFileSystem.hpp"

#include "stream/rIStringStream.hpp"
#include "stream/rOStringStream.hpp"

class TestFilesystem : public riFileSystem {
public:
	~TestFilesystem();
	virtual rIStream* OpenReadFileRef(const rString& path) override;
	virtual void CloseReadFileRef(rIStream* stream) override;

	virtual rOStream* OpenWriteFileRef(const rString& path);
	virtual void CloseWriteFileRef(rOStream* stream);

	void SetSavedSata(const rString& path, const rString& data);

	virtual bool Exists(const rString& path);
	virtual bool FileSize(const rString& path, size_t& size) const ;

	void Clear();

	std::set<rIStringStream*> openReadableFiles;
	std::map<rOStringStream*, rString> openWriteableFiles;
	std::map<rString, rString> savedData;
};