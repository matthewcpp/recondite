#pragma once

#include "rBuild.hpp"
#include "rString.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

#include "rFileSystem.hpp"

namespace recondite {
	class RECONDITE_API ArchiveWriter {
	public:
		ArchiveWriter();
		~ArchiveWriter();

	public:
		bool SetKey(const rString& key, const char* data, size_t dataSize);
		bool SetKey(const rString& key, const rString& filePath);

		void DeleteKey(const rString& key);
		void Write(rOStream& stream);

	private:
		struct Impl;
		Impl* _impl;
	};

	class RECONDITE_API ArchiveEntryStream : public rIStream{
	public:
		ArchiveEntryStream(rIStream* stream, size_t offset, size_t size);
		~ArchiveEntryStream();

		virtual rIStream& Read(char* buffer, size_t size);
		virtual size_t ReadCount() const;
		virtual int Peek();
		virtual void Seek(size_t pos);
		virtual void Seek(size_t pos, rSeekMode seekFrom);
		virtual size_t Pos();
		virtual bool IsOk() const;
		virtual rIStream& Get(char& ch);

		virtual rIStream& operator >> (char& c);
		virtual rIStream& operator >> (unsigned char& c);
		virtual rIStream& operator >> (short& s);
		virtual rIStream& operator >> (unsigned short& s);
		virtual rIStream& operator >> (int& i);
		virtual rIStream& operator >> (unsigned int& i);
		virtual rIStream& operator >> (long& l);
		virtual rIStream& operator >> (unsigned long& l);
		virtual rIStream& operator >> (float& f);

		virtual operator bool() const;

	private:
		struct Impl;
		Impl* _impl;
	};

	class RECONDITE_API ArchiveReader {
	public:
		ArchiveReader(riFileSystem* fileSystem);
		~ArchiveReader();

	public:
		bool LoadFromFilesystem(const rString& path);

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