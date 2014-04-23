#include "stream/rIStream.hpp"

rIStream& rIStream::operator >> (char c){
	return Read(&c, 1);
}

rIStream& rIStream::operator >> (unsigned char c){
	return Read((char*)&c, 1);
}

rIStream& rIStream::operator >> (short s){
	return Read((char*)&s, 2);
}

rIStream& rIStream::operator >> (unsigned short s){
	return Read((char*)&s, 2);
}

rIStream& rIStream::operator >> (int i){
	return Read((char*)&i, 4);
}

rIStream& rIStream::operator >> (unsigned int i){
	return Read((char*)&i, 4);
}

rIStream& rIStream::operator >> (float f){
	return Read((char*)&f, 4);
}

rIStream::operator bool() const{
	return IsOk();
}