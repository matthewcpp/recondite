#include "rArchive.hpp"

#include <map>
#include <memory>
#include <vector>
#include <cstdint>
#include <set>
#include <algorithm>

#include "stream/rIFileStream.hpp"
#include "stream/rOStringStream.hpp"

namespace recondite {
	class ArchiveEntry {
	public:
		virtual size_t GetSize() const = 0;
		virtual void WriteData(rOStream& stream) = 0;
		virtual ~ArchiveEntry() {}
	};

	class DataArchiveEntry : public ArchiveEntry {
	public:
		DataArchiveEntry(const char* data, size_t dataSize);

	public:
		virtual size_t GetSize() const override;
		virtual void WriteData(rOStream& stream) override;

	private:
		std::vector<char> _buffer;
	};

	class FileArchiveEntry : public ArchiveEntry {
	public:
		FileArchiveEntry(const rString& path, size_t size);

	public:
		virtual size_t GetSize() const override;
		virtual void WriteData(rOStream& stream) override;

	private:
		size_t _size;
		rString _path;
	};

	struct PathData {
		uint32_t pathOffset;
		uint32_t pathSize;
		uint32_t dataOffset;
		uint32_t dataSize;
	};

	struct rArchiveHeader {
		uint32_t magicNumber;
		uint32_t entryCount;
		uint32_t keyDataSize;
	};

#define rARCHIVE_HEADER_MAGIC_NUM 1984

	struct ArchiveData::Impl {
		std::map < rString, std::unique_ptr<ArchiveEntry>> entries;
	};

	ArchiveData::ArchiveData() {
		_impl = new Impl();
	}

	ArchiveData::~ArchiveData() {
		delete _impl;
	}

	bool ArchiveData::SetKeyFromData(const rString& key, const char* data, size_t dataSize) {
		DataArchiveEntry* entry = new DataArchiveEntry(data, dataSize);
		_impl->entries.emplace(key, entry);

		return true;
	}

	bool ArchiveData::SetKeyFromFilePath(const rString& key, const rString& filePath, size_t fileSize) {
		FileArchiveEntry* entry = new FileArchiveEntry(filePath, fileSize);
		_impl->entries.emplace(key, entry);

		return true;
	}

	void ArchiveData::DeleteKey(const rString& key) {
		_impl->entries.erase(key);
	}

	bool ArchiveData::HasKey(const rString& key) const {
		return _impl->entries.count(key) > 0;
	}

	size_t ArchiveData::GetNumKeys() const {
		return _impl->entries.size();
	}

	struct Archive::Impl {
		std::set<ArchiveEntryStream*> openEntries;
		riFileSystem* fileSystem;
		rArchiveHeader header;
		rIStream* archiveStream;
		rString fileSystemPath;

		int BinarySearch(const rString& path, int begin, int end);
		void GetEntryInfo(int index, PathData& data);
		uint32_t AbsolutePathOffset(uint32_t relativePathOffset);
	};

	Archive::Archive(riFileSystem* fileSystem) {
		_impl = new Impl();
		_impl->fileSystem = fileSystem;
		_impl->archiveStream = nullptr;
	}

	Archive::~Archive() {
		Close();
		delete _impl;
	}

	bool Archive::LoadFromFilesystem(const rString& path) {
		auto archiveStream =_impl->fileSystem->OpenReadFileRef(path);

		if (archiveStream && archiveStream->IsOk()) {
			archiveStream->Read((char*)&_impl->header, sizeof(rArchiveHeader));

			if (_impl->header.magicNumber != rARCHIVE_HEADER_MAGIC_NUM) {
				return false;
			}

			_impl->fileSystemPath = path;
			_impl->archiveStream = archiveStream;
			return true;
		}

		return false;
	}

	void Archive::Close() {
		if (_impl->archiveStream) {
			_impl->fileSystem->CloseReadFileRef(_impl->archiveStream);
			_impl->archiveStream = nullptr;

			for (auto openEntry : _impl->openEntries)
				delete openEntry;

			_impl->openEntries.clear();
			_impl->fileSystemPath.clear();
		}
	}

	bool Archive::IsOpen() const {
		return _impl->archiveStream != nullptr;
	}

	uint32_t Archive::Impl::AbsolutePathOffset(uint32_t relativePathOffset) {
		//header + lookup table + relative offset
		return sizeof(rArchiveHeader) + (sizeof(PathData) * header.entryCount) + relativePathOffset;
	}

	void Archive::Impl::GetEntryInfo(int index, PathData& data) {
		uint32_t dataOffset = sizeof(rArchiveHeader) + (index * sizeof(PathData));

		archiveStream->Seek(dataOffset, rSeekMode::Beginning);
		archiveStream->Read((char*)&data, sizeof(PathData));
	}

	int Archive::Impl::BinarySearch(const rString& path, int begin, int end) {
		int mid = (begin + end) / 2;
		PathData pathData;
		GetEntryInfo(mid, pathData);

		std::vector<char> searchPathBuffer(pathData.pathSize);
		archiveStream->Seek(AbsolutePathOffset(pathData.pathOffset), rSeekMode::Beginning);
		archiveStream->Read(searchPathBuffer.data(), pathData.pathSize);

		rString searchPath(searchPathBuffer.data(), searchPathBuffer.size());

		int result = path.compare(searchPath);

		if (result == 0)
			return mid;
		else if (begin == end)
			return -1; // item not found;
		else if (result < 0)
			return BinarySearch(path, begin, mid - 1);
		else //(result > 0)
			return BinarySearch(path, mid + 1, end);
	}

	bool Archive::HasKey(const rString& key) {
		if (_impl->archiveStream == nullptr)
			return false;
		else
			return _impl->BinarySearch(key, 0, _impl->header.entryCount - 1) != -1;
	}

	size_t Archive::GetNumKeys() const {
		return _impl->header.entryCount;
	}

	bool Archive::GetKeyByIndex(size_t index, rString& key) {
		if (index >= _impl->header.entryCount) {
			return false;
		}
		else {
			PathData pathData;
			_impl->GetEntryInfo(index, pathData);

			std::vector<char> searchPathBuffer(pathData.pathSize);
			_impl->archiveStream->Seek(_impl->AbsolutePathOffset(pathData.pathOffset), rSeekMode::Beginning);
			_impl->archiveStream->Read(searchPathBuffer.data(), pathData.pathSize);

			key.assign(searchPathBuffer.data(), searchPathBuffer.size());
			return true;
		}
	}

	ArchiveEntryStream* Archive::OpenStream(const rString& key) {
		ArchiveEntryStream* result = nullptr;

		if (IsOpen()) {
			int index = _impl->BinarySearch(key, 0, _impl->header.entryCount - 1);

			if (index >= 0) {
				PathData pathData;
				_impl->GetEntryInfo(index, pathData);

				rIStream* archiveFile = _impl->fileSystem->OpenReadFileRef(_impl->fileSystemPath);
				result = new ArchiveEntryStream(archiveFile, pathData.dataOffset, pathData.dataSize);
				_impl->openEntries.emplace(result);
			}
		}

		return result;
	}

	bool Archive::CloseStream(ArchiveEntryStream* stream) {
		auto result = _impl->openEntries.find(stream);

		if (result != _impl->openEntries.end()) {
			delete *result;
			_impl->openEntries.erase(result);

			return true;
		}
		else {
			return false;
		}
	}

	void ArchiveData::Write(rOStream& stream) {
		//gather all paths in the archive
		std::vector<rString> keys;
		for (auto const& element : _impl->entries)
			keys.push_back(element.first);

		std::vector<PathData> pathDataVector(keys.size());

		//build header + lookup table
		uint32_t pathOffset = 0;
		uint32_t dataOffset = 0;

		for (size_t i = 0; i < keys.size(); i++) {
			pathDataVector[i].pathOffset = pathOffset;
			pathDataVector[i].pathSize = keys[i].size();

			pathDataVector[i].dataOffset = dataOffset;
			pathDataVector[i].dataSize = _impl->entries[keys[i]]->GetSize();

			pathOffset += pathDataVector[i].pathSize;
			dataOffset += pathDataVector[i].dataSize;
		}

		rArchiveHeader header;
		header.magicNumber = rARCHIVE_HEADER_MAGIC_NUM;
		header.entryCount = keys.size();
		header.keyDataSize = pathOffset;

		rOStringStream& stringstream = (rOStringStream&)stream;

		//write header
		uint32_t dataCount = keys.size();
		stream.Write((const char*)&header, sizeof(rArchiveHeader));

		size_t strsize = stringstream.Str().size();

		//write lookup table
		stream.Write((const char*)pathDataVector.data(), sizeof(PathData) * pathDataVector.size());

		strsize = stringstream.Str().size();

		//write key data
		for (size_t i = 0; i < keys.size(); i++) {
			stream.Write(keys[i].c_str(), keys[i].size());
		}

		strsize = stringstream.Str().size();

		//write archive data
		for (size_t i = 0; i < keys.size(); i++) {
			_impl->entries[keys[i]]->WriteData(stream);
		}

		strsize = stringstream.Str().size();
	}

	DataArchiveEntry::DataArchiveEntry(const char* data, size_t dataSize) {
		_buffer.resize(dataSize);
		memcpy(_buffer.data(), data, dataSize);
	}

	size_t DataArchiveEntry::GetSize() const {
		return _buffer.size();
	}

	void DataArchiveEntry::WriteData(rOStream& stream) {
		stream.Write(_buffer.data(), _buffer.size());
	}

	FileArchiveEntry::FileArchiveEntry(const rString& path, size_t size) {
		_path = path;
		_size = size;
	}

	size_t FileArchiveEntry::GetSize() const {
		return _size;
	}

	void FileArchiveEntry::WriteData(rOStream& stream) {
		const int BUFFER_SIZE = 1024;

		rIFileStream srcFile(_path);

		if (srcFile.IsOk()) {
			char buffer[BUFFER_SIZE];
			
			size_t bytesRead = 0;

			do {
				srcFile.Read(buffer, BUFFER_SIZE);
				size_t readCount = srcFile.ReadCount();

				stream.Write(buffer, readCount);

			} while (bytesRead < _size);
		}
	}
}