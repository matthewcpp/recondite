#include "rString.hpp"

rString::rString (const rString& str){
	m_str = str.m_str;
}

const char* rString::c_str() const{
	return m_str.c_str();
}

size_t rString::size() const{
	return m_str.size();
}

size_t rString::length() const{
	return m_str.length();
}

rString& rString::operator=(const rString& str){
	m_str = str.m_str;
	return *this;
}

rString& rString::operator=(const char* str){
	m_str.assign(str);
	return *this;
}

char& rString::operator[](int index){
	return m_str[index];
}

rString rString::operator + (const rString& str) const{
	rString result;
	result.m_str = m_str + str.m_str;

	return result;
}

rString& rString::operator += (const rString& str){
	m_str += str.m_str;
	return *this;
}

rString rString::operator + (char c) const{
	rString result;
	result.m_str = m_str + c;
	return result;
}

rString& rString::operator += (char c){
	m_str += c;
	return *this;
}

bool rString::operator == (const rString& str) const{
	return m_str == str.m_str;
}

bool rString::operator != (const rString& str) const{
	return m_str != str.m_str;
}

bool rString::operator < (const rString& str) const{
	return m_str < str.m_str;
}

bool rString::operator <= (const rString& str) const{
	return m_str <= str.m_str;
}

bool rString::operator > (const rString& str) const{
	return m_str <= str.m_str;
}

bool rString::operator >= (const rString& str) const{
	return m_str >= str.m_str;
}

rString::operator const char*() const{
	return c_str();
}
