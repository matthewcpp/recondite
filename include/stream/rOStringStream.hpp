#ifndef R_OSTRINGSTREAM_HPP
#define R_OSTRINGSTREAM_HPP

#include <sstream>

#include "rBuild.hpp"
#include "stream/rOStream.hpp"

#include "rString.hpp"

class RECONDITE_API rOStringStream : public rOStream{
public:
	rOStringStream();
	rOStringStream(const rString& str);

public:

	virtual rOStream& Write(const char* buffer, size_t size) = 0;

	virtual void Seek(size_t pos) = 0;
	virtual size_t Pos() = 0;

	virtual bool IsOk() const = 0;

	virtual rOStream& operator << (char c);
	virtual rOStream& operator << (const char* str);
	virtual rOStream& operator << (unsigned char c);
	virtual rOStream& operator << (short s);
	virtual rOStream& operator << (unsigned short s);
	virtual rOStream& operator << (int i);
	virtual rOStream& operator << (unsigned int i);
	virtual rOStream& operator << (float f);

	virtual operator bool() const;

private:
	std::ostringstream m_stream;
};

#endif