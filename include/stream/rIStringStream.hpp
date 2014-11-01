#ifndef R_ISTRINGSTREAM_HPP
#define R_ISTRINGSTREAM_HPP

#include <sstream>

#include "rBuild.hpp"
#include "stream/rIStream.hpp"

#include "rString.hpp"

class RECONDITE_API rIStringStream : public rIStream{
public:
	rIStringStream();
	rIStringStream(const rString& str);

public:

	virtual rIStream& Read(char* buffer, size_t size);
	virtual size_t ReadCount() const;
	virtual int Peek();
	virtual void Seek(size_t pos);
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
	virtual rIStream& operator >> (rString& str);

	virtual operator bool() const;

private:
	std::istringstream m_stream;
};

#endif