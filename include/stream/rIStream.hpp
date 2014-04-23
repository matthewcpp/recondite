#ifndef R_ISTREAM_HPP
#define R_ISTREAM_HPP

#include <cstddef>

#include "rBuild.hpp"

class RECONDITE_API rIStream{
public:

	virtual rIStream& Read(char* buffer, size_t size) = 0;
	virtual size_t ReadCount() const = 0;
	virtual int Peek() = 0;
	virtual void Seek(size_t pos) = 0;
	virtual size_t Pos() = 0;
	virtual bool IsOk() const = 0;

	rIStream& operator >> (char c);
	rIStream& operator >> (unsigned char c);
	rIStream& operator >> (short s);
	rIStream& operator >> (unsigned short s);
	rIStream& operator >> (int i);
	rIStream& operator >> (unsigned int i);
	rIStream& operator >> (float f);

	operator bool() const;
};

#endif