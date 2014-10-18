#include "stream/rIFileStream.hpp"

rIFileStream::rIFileStream(){
}

rIFileStream::rIFileStream(const rString& path){
	Open(path);
}

void rIFileStream::Open(const rString& path){
	m_file.open(path.c_str(), std::ios::binary);
}

void rIFileStream::Close(){
	m_file.close();
}

rIStream& rIFileStream::Read(char* buffer, size_t size){
	m_file.read(buffer, size);
	return *this;
}

size_t rIFileStream::ReadCount() const{
	return m_file.gcount();
}

int rIFileStream::Peek(){
	return m_file.peek();
}

void rIFileStream::Seek(size_t pos){
	m_file.seekg(pos);
}

size_t rIFileStream::Pos(){
	return m_file.tellg();
}

bool rIFileStream::IsOk() const{
	return !m_file.fail();
}

rIStream& rIFileStream::Get(char& ch){
	m_file.get(ch);
	return *this;
}

rIStream& rIFileStream::operator >> (char& c){
	m_file >> c;
	return *this;
}

rIStream& rIFileStream::operator >> (unsigned char& c){
	m_file >> c;
	return *this;
}

rIStream& rIFileStream::operator >> (short& s){
	m_file >> s;
	return *this;
}

rIStream& rIFileStream::operator >> (unsigned short& s){
	m_file >> s;
	return *this;
}

rIStream& rIFileStream::operator >> (int& i){
	m_file >> i;
	return *this;
}

rIStream& rIFileStream::operator >> (unsigned int& i){
	m_file >> i;
	return *this;
}

rIStream& rIFileStream::operator >> (float& f){
	m_file >> f;
	return *this;
}

rIFileStream::operator bool() const{
	return IsOk();
}