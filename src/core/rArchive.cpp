#include "rArchive.hpp"

#include <map>
#include <memory>
#include <vector>
#include <cstdint>
#include <set>
#include <algorithm>

#include "stream/rIFileStream.hpp"

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

	struct ArchiveWriter::Impl {
		std::map < rString, std::unique_ptr<ArchiveEntry>> entries;
	};

	ArchiveWriter::ArchiveWriter() {
		_impl = new Impl();
	}

	ArchiveWriter::~ArchiveWriter() {
		delete _impl;
	}

	bool ArchiveWriter::SetKey(const rString& key, const char* data, size_t dataSize) {
		DataArchiveEntry* entry = new DataArchiveEntry(data, dataSize);
		_impl->entries.emplace(key, entry);

		return true;
	}

	bool ArchiveWriter::SetKey(const rString& key, const rString& filePath) {
		return true;
	}

	void ArchiveWriter::DeleteKey(const rString& key) {
		_impl->entries.erase(key);
	}

	struct ArchiveReader::Impl {
		std::set<ArchiveEntryStream*> openEntries;
		riFileSystem* fileSystem;
		rArchiveHeader header;
		rIStream* archiveStream;
		rString fileSystemPath;

		int BinarySearch(const rString& path, int begin, int end);
		void GetEntryInfo(int index, PathData& data);
		uint32_t AbsolutePathOffset(uint32_t relativePathOffset);
	};

	ArchiveReader::ArchiveReader(riFileSystem* fileSystem) {
		_impl = new Impl();
		_impl->fileSystem = fileSystem;
	}

	ArchiveReader::~ArchiveReader() {
		_impl->fileSystem->CloseReadFileRef(_impl->archiveStream);
		delete _impl;
	}

	bool ArchiveReader::LoadFromFilesystem(const rString& path) {
		auto archiveStream =_impl->fileSystem->OpenReadFileRef(path);

		if (archiveStream->IsOk()) {
			archiveStream->Read((char*)&_impl->header, sizeof(rArchiveHeader));

			if (_impl->header.magicNumber != rARCHIVE_HEADER_MAGIC_NUM) {
				return false;
			}

			_impl->fileSystemPath = path;
			return true;
		}

		return false;
	}

	uint32_t ArchiveReader::Impl::AbsolutePathOffset(uint32_t relativePathOffset) {
		//header + lookup table + relative offset
		return sizeof(rArchiveHeader) + (sizeof(PathData) * header.entryCount) + relativePathOffset;
	}

	void ArchiveReader::Impl::GetEntryInfo(int index, PathData& data) {
		uint32_t dataOffset = sizeof(rArchiveHeader) + (index * sizeof(PathData));

		archiveStream->Seek(dataOffset, rSeekMode::Beginning);
		archiveStream->Read((char*)&data, sizeof(PathData));
	}

	int ArchiveReader::Impl::BinarySearch(const rString& path, int begin, int end) {
		int mid = (begin + end) / 2;
		PathData pathData;
		GetEntryInfo(mid, pathData);

		std::vector<char> searchPathBuffer(pathData.pathSize);
		archiveStream->Seek(AbsolutePathOffset(pathData.pathOffset), rSeekMode::Beginning);
		archiveStream->Read(searchPathBuffer.data(), pathData.pathSize);

		rString searchPath(searchPathBuffer.data(), searchPathBuffer.size());

		int result = searchPath.compare(searchPath);

		if (result == 0)
			return mid;
		else if (begin == end)
			return -1; // item not found;
		else if (result < 0)
			return BinarySearch(path, begin, mid - 1);
		else //(result > 0)
			return BinarySearch(path, mid + 1, end);
	}

	ArchiveEntryStream* ArchiveReader::OpenStream(const rString& key) {
		ArchiveEntryStream* result = nullptr;;
		int index = _impl->BinarySearch(key, 0, _impl->header.entryCount - 1);

		if (index >= 0) {
			PathData pathData;
			_impl->GetEntryInfo(index, pathData);

			rIStream* archiveFile = _impl->fileSystem->OpenReadFileRef(_impl->fileSystemPath);
			result = new ArchiveEntryStream(archiveFile, pathData.dataOffset, pathData.dataSize);
			_impl->openEntries.emplace(result);
		}

		return result;
	}

	bool ArchiveReader::CloseStream(ArchiveEntryStream* stream) {
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

	void ArchiveWriter::Write(rOStream& stream) {
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

		//write header
		uint32_t dataCount = keys.size();
		stream.Write((const char*)&header, sizeof(rArchiveHeader));

		//write lookup table
		stream.Write((const char*)pathDataVector.data(), sizeof(PathData) * pathDataVector.size());

		//write key data
		for (size_t i = 0; i < keys.size(); i++) {
			stream.Write(keys[i].c_str(), keys[i].size());
		}

		//write archive data
		for (size_t i = 0; i < keys.size(); i++) {
			_impl->entries[keys[i]]->WriteData(stream);
		}
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

	struct ArchiveEntryStream::Impl{
		rIStream* stream;
		size_t offset;
		size_t size;

		Impl(rIStream* _stream, size_t _offset, size_t _size) : 
			stream(_stream), offset(_offset), size(_size) {}
	};

	ArchiveEntryStream::ArchiveEntryStream(rIStream* stream, size_t offset, size_t size) {
		_impl = new Impl(stream, offset, size);
		
		_impl->stream->Seek(offset, rSeekMode::Beginning);
	}

	ArchiveEntryStream::~ArchiveEntryStream() {
		delete _impl->stream;
		delete _impl;
	}

	rIStream& ArchiveEntryStream::Read(char* buffer, size_t size) {
		size_t currentPos = _impl->stream->Pos();
		size_t numBytes = std::min(size, _impl->offset);
		
		size_t newPos = currentPos + numBytes;
		size_t maxPos = _impl->offset + _impl->size;
		if (newPos > maxPos)
			numBytes -= newPos - maxPos;

		_impl->stream->Read(buffer, numBytes);

		return *this;
	}

	size_t ArchiveEntryStream::ReadCount() const{
		return _impl->stream->ReadCount();
	}

	int ArchiveEntryStream::Peek() {
		return _impl->stream->Peek();
	}

	void ArchiveEntryStream::Seek(size_t pos) {
		return Seek(pos, rSeekMode::Beginning);
	}

	void ArchiveEntryStream::Seek(size_t pos, rSeekMode seekFrom) {
		switch (seekFrom){
			case rSeekMode::Beginning:
				pos = _impl->offset + pos;
				break;

			case rSeekMode::Current:
				pos = _impl->stream->Pos() + pos;
				break;

			case rSeekMode::End:
				pos = _impl->offset + _impl->size - pos;
				break;
		}

		pos = std::max(pos, _impl->offset);
		pos = std::min(pos, _impl->offset + _impl->size);

		_impl->stream->Seek(pos);
	}

	size_t ArchiveEntryStream::Pos() {
		return _impl->stream->Pos() - _impl->offset;
	}

	bool ArchiveEntryStream::IsOk() const {
		return _impl->stream->IsOk();
	}

	rIStream& ArchiveEntryStream::Get(char& ch) {
		if (_impl->stream->Pos() >= _impl->offset + _impl->size)
			ch = -1;
		else
			_impl->stream->Get(ch);

		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (char& c) {
		*_impl->stream >> c;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (unsigned char& c) {
		*_impl->stream >> c;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (short& s) {
		*_impl->stream >> s;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (unsigned short& s) {
		*_impl->stream >> s;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (int& i) {
		*_impl->stream >> i;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (unsigned int& i) {
		*_impl->stream >> i;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (long& l) {
		*_impl->stream >> l;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (unsigned long& l) {
		*_impl->stream >> l;
		return *this;
	}

	rIStream& ArchiveEntryStream::operator >> (float& f) {
		*_impl->stream >> f;
		return *this;
	}

	ArchiveEntryStream::operator bool() const {
		return _impl->stream->IsOk();
	}

}