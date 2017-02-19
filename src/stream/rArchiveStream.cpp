#include "stream/rArchiveStream.hpp"

#include <algorithm>

namespace recondite {
	struct ArchiveEntryStream::Impl {
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
		size_t numBytes = std::max(size, _impl->offset);

		size_t newPos = currentPos + numBytes;
		size_t maxPos = _impl->offset + _impl->size;
		if (newPos > maxPos)
			numBytes -= newPos - maxPos;

		_impl->stream->Read(buffer, numBytes);

		return *this;
	}

	size_t ArchiveEntryStream::ReadCount() const {
		return _impl->stream->ReadCount();
	}

	int ArchiveEntryStream::Peek() {
		if (Pos() >= _impl->size)
			return -1;
		else
			return _impl->stream->Peek();
	}

	void ArchiveEntryStream::Seek(size_t pos) {
		return Seek(pos, rSeekMode::Beginning);
	}

	void ArchiveEntryStream::Seek(size_t pos, rSeekMode seekFrom) {
		switch (seekFrom) {
		case rSeekMode::Beginning:
			pos = _impl->offset + pos;
			break;

		case rSeekMode::Current:
			pos = _impl->stream->Pos() + pos;
			break;

		case rSeekMode::End:
			pos = _impl->offset + _impl->size - std::min(pos, _impl->size);
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