#ifndef R_IFILESTREAM_HPP
#define R_IFILESTREAM_HPP

#include <fstream>

#include "rBuild.hpp"
#include "stream/rIStream.hpp"

#include "rString.hpp"

class RECONDITE_API rIFileStream : public rIStream{
public:
	rIFileStream();
	rIFileStream(const rString& path);

	void Open(const rString& path);
	void Close();
	
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
	std::ifstream m_file;
};

#endif