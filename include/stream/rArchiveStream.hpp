#pragma once

#include "rBuild.hpp"

#include "stream/rIStream.hpp"

namespace recondite {
	class RECONDITE_API ArchiveEntryStream : public rIStream {
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
}