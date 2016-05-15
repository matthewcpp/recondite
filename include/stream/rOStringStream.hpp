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

	virtual rOStream& Write(const char* buffer, size_t size);

	virtual void Seek(size_t pos);
	virtual void Seek(size_t pos, rSeekMode seekFrom);

	virtual size_t Pos();

	virtual bool IsOk() const;

	virtual rOStream& operator << (char c);
	virtual rOStream& operator << (const char* str);
	virtual rOStream& operator << (unsigned char c);
	virtual rOStream& operator << (short s);
	virtual rOStream& operator << (unsigned short s);
	virtual rOStream& operator << (int i);
	virtual rOStream& operator << (unsigned int i);
	virtual rOStream& operator << (long l);
	virtual rOStream& operator << (unsigned long l);
	virtual rOStream& operator << (float f);
	virtual rOStream& operator << (const rString& str);

	virtual operator bool() const;

	rString Str() const;

private:
	std::ostringstream m_stream;
};

#endif