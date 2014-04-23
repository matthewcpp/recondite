#ifndef R_OSTREAM_HPP
#define R_OSTREAM_HPP

#include <cstddef>
#include <cstring>

#include "rBuild.hpp"

class RECONDITE_API rOStream{
public:

	virtual rOStream& Write(const char* buffer, size_t size) = 0;

	virtual void Seek(size_t pos) = 0;
	virtual size_t Pos() = 0;

	virtual bool IsOk() const = 0;

	virtual rOStream& operator << (char c) = 0;
	virtual rOStream& operator << (const char* str) = 0;
	virtual rOStream& operator << (unsigned char c) = 0;
	virtual rOStream& operator << (short s) = 0;
	virtual rOStream& operator << (unsigned short s) = 0;
	virtual rOStream& operator << (int i) = 0;
	virtual rOStream& operator << (unsigned int i) = 0;
	virtual rOStream& operator << (float f) =0;

	virtual operator bool() const = 0;
};

#endif