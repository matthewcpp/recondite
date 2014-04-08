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

bool rString::operator == (const char* str) const{
	return m_str == str;
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

char rString::first() const{
	if (m_str.length() > 0)
		return m_str[0];
	else
		return 0;
}

char rString::last() const{
	if (m_str.length() > 0)
		return m_str[m_str.length() - 1];
	else
		return 0;
}

rString rString::substr (size_t pos, size_t len) const{
	rString result;
	result.m_str = m_str.substr(pos,len);

	return result;
}

size_t rString::find_first_of(char c) const{
	return m_str.find_first_of(c);
}

size_t rString::find_last_of(char c) const{
	return m_str.find_last_of(c);
}

void rString::clear(){
	m_str.clear();
}

size_t rString::npos = std::numeric_limits<std::size_t>::max();