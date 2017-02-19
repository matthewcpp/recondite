#pragma once

#include "rBuild.hpp"
#include "rString.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

#include "rFileSystem.hpp"

#include "stream/rArchiveStream.hpp"

namespace recondite {
	class RECONDITE_API ArchiveData {
	public:
		ArchiveData();
		~ArchiveData();

	public:
		bool SetKeyFromData(const rString& key, const char* data, size_t dataSize);
		bool SetKeyFromFilePath(const rString& key, const rString& filePath, size_t fileSize);

		bool HasKey(const rString& key) const;

		size_t GetNumKeys() const;

		void DeleteKey(const rString& key);
		void Write(rOStream& stream);

	private:
		struct Impl;
		Impl* _impl;
	};

	class RECONDITE_API Archive {
	public:
		Archive(riFileSystem* fileSystem);
		~Archive();

	public:
		bool LoadFromFilesystem(const rString& path);
		bool IsOpen() const;
		void Close();

	public:
		ArchiveEntryStream* OpenStream(const rString& key);
		bool CloseStream(ArchiveEntryStream* stream);

	public:
		bool HasKey(const rString& key);
		size_t GetNumKeys() const;
		bool GetKeyByIndex(size_t index, rString& key);

	private:
		struct Impl;
		Impl* _impl;
	};
}