#ifndef R_OFILESTREAM_HPP
#define R_OFILESTREAM_HPP

#include <fstream>

#include "rBuild.hpp"
#include "stream/rOStream.hpp"

#include "rString.hpp"

class RECONDITE_API rOFileStream : public rOStream{
public:
	rOFileStream();
	rOFileStream(const rString& path);

	void Open(const rString& path);
	void Close();

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

	virtual operator bool() const;

private:
	std::ofstream m_file;
};

#endif