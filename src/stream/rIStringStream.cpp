#include "stream/rIStringStream.hpp"

rIStringStream::rIStringStream(){

}

rIStringStream::rIStringStream(const rString& str)
:m_stream(str.c_str())
{

}

rIStream& rIStringStream::Read(char* buffer, size_t size){
	m_stream.read(buffer,size);
	return *this;
}

size_t rIStringStream::ReadCount() const{
	return m_stream.gcount();
}

int rIStringStream::Peek(){
	return m_stream.peek();
}

void rIStringStream::Seek(size_t pos){
	m_stream.seekg(pos);
}

size_t rIStringStream::Pos(){
	return m_stream.tellg();
}

bool rIStringStream::IsOk() const{
	return !m_stream.fail();
}

rIStream& rIStringStream::Get(char& ch){
	m_stream.get(ch);
	return *this;
}

rIStream& rIStringStream::operator >> (char& c){
	m_stream >> c;
	return *this;
}

rIStream& rIStringStream::operator >> (unsigned char& c){
	m_stream >> c;
	return *this;
}

rIStream& rIStringStream::operator >> (short& s){
	m_stream >> s;
	return *this;
}

rIStream& rIStringStream::operator >> (unsigned short& s){
	m_stream >> s;
	return *this;
}

rIStream& rIStringStream::operator >> (int& i){
	m_stream >> i;
	return *this;
}

rIStream& rIStringStream::operator >> (unsigned int& i){
	m_stream >> i;
	return *this;
}

rIStream& rIStringStream::operator >> (float& f){
	m_stream >> f;
	return *this;
}

rIStream& rIStringStream::operator >> (rString& str){
	std::string s;
	m_stream >> s;

	if (s.length() > 0)
		str.assign(s.c_str(), s.length());

	return *this;
}

rIStringStream::operator bool() const{
	return IsOk();
}
