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

	virtual rIStream& operator >> (char& c) = 0;
	virtual rIStream& operator >> (unsigned char& c) = 0;
	virtual rIStream& operator >> (short& s) = 0;
	virtual rIStream& operator >> (unsigned short& s) = 0;
	virtual rIStream& operator >> (int& i) = 0;
	virtual rIStream& operator >> (unsigned int& i) = 0;
	virtual rIStream& operator >> (float& f) = 0;

	virtual operator bool() const = 0;
};

#endif