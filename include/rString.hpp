#ifndef R_STRING_HPP
#define R_STRING_HPP

#include <string>

class rString{
public:
	rString(){}
	rString (const char* str) : m_str(str){}
	rString (const char* str, size_t length) : m_str(str, length) {}
	rString (const rString& str);
	
	const char* c_str() const;
	
	size_t size() const;
	size_t length() const;

	operator const char*() const;

	bool operator == (const rString& str) const;
	bool operator != (const rString& str) const;
	bool operator < (const rString& str) const;
	bool operator <= (const rString& str) const;
	bool operator > (const rString& str) const;
	bool operator >= (const rString& str) const;
	
	char& operator[](int index);
	rString& operator=(const rString& str);
	rString& operator=(const char* str);
	
	rString operator + (const rString& str) const;
	rString& operator += (const rString& str);
	
	rString operator + (char c) const;
	rString& operator += (char c);

private:
	std::string m_str;
};

#endif