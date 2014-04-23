#ifndef R_OSTREAM_HPP
#define R_OSTREAM_HPP

#include <cstddef>

#include "rBuild.hpp"

class RECONDITE_API rIStream{
public:

	virtual void Write(const char* buffer, size_t size) = 0;
	virtual void Seek(size_t pos) = 0;
	virtual size_t Pos() = 0;


};

#endif