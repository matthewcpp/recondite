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
	m_file.seekg(std::ios::beg, pos);
}

size_t rIFileStream::Pos(){
	return m_file.tellg();
}

bool rIFileStream::IsOk() const{
	return !m_file.fail();
}