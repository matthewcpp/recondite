#include "stream/rOStringStream.hpp"

rOStringStream::rOStringStream(){
}

rOStringStream::rOStringStream(const rString& str){
	m_stream << str.c_str();
}

rOStream& rOStringStream::Write(const char* buffer, size_t size){
	m_stream.write(buffer, size);
	return *this;
}

void rOStringStream::Seek(size_t pos){
	m_stream.seekp(pos);
}

size_t rOStringStream::Pos(){
	return m_stream.tellp();
}

bool rOStringStream::IsOk() const{
	return !m_stream.fail();
}

rOStream& rOStringStream::operator << (const rString& str){
	m_stream << str.c_str();
	return *this;
}

rOStream& rOStringStream::operator << (char c){
	m_stream << c;
	return *this;
}

rOStream& rOStringStream::operator << (const char* str){
	m_stream << str;
	return *this;
}

rOStream& rOStringStream::operator << (unsigned char c){
	m_stream << c;
	return *this;
}

rOStream& rOStringStream::operator << (short s){
	m_stream << s;
	return *this;
}

rOStream& rOStringStream::operator << (unsigned short s){
	m_stream << s;
	return *this;
}

rOStream& rOStringStream::operator << (int i){
	m_stream << i;
	return *this;
}

rOStream& rOStringStream::operator << (unsigned int i){
	m_stream << i;
	return *this;
}

rOStream& rOStringStream::operator << (long l){
	m_stream << l;
	return *this;
}

rOStream& rOStringStream::operator << (unsigned long l){
	m_stream << l;
	return *this;
}

rOStream& rOStringStream::operator << (float f){
	m_stream << f;
	return *this;
}

rOStringStream::operator bool() const{
	return IsOk();
}


rString rOStringStream::Str() const{
	return m_stream.str().c_str();
}