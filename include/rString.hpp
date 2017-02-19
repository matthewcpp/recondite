#ifndef R_STRING_HPP
#define R_STRING_HPP

#include <string>
#include <vector>
#include <limits>
#include <sstream>

#include "rBuild.hpp"

class RECONDITE_API rString{
public:
	rString(){}
	rString (const char* str) : m_str(str){}
	rString (const char* str, size_t length) : m_str(str, length) {}
	rString (const rString& str);
	rString (size_t n, char c): m_str(n,c){}
	
	const char* c_str() const;
	const char* data() const;

	void assign(const char* str, int len);
	size_t find(const rString& str, size_t pos = 0);
	size_t find_last_of(const char* str) const;
	rString& replace (size_t pos,  size_t len,  const rString& s);
	
	size_t size() const;
	size_t length() const;
	void resize(size_t size);
	bool empty() const;

	void clear();
	void append(const char* str);

	operator const char*() const;

	bool operator == (const rString& str) const;
	bool operator == (const char* str) const;

	bool operator != (const rString& str) const;
	bool operator < (const rString& str) const;
	bool operator <= (const rString& str) const;
	bool operator > (const rString& str) const;
	bool operator >= (const rString& str) const;

	char first() const;
	char last() const;

	int compare(const char* str) const;

	void pop_back();
	
	rString substr (size_t pos = 0, size_t len = npos) const;
	size_t find_first_of(char c) const;
	size_t find_last_of(char c) const;

	char& operator[](int index);
	rString& operator=(const rString& str);
	rString& operator=(const char* str);
	
	rString operator + (const rString& str) const;
	rString& operator += (const rString& str);
	
	rString operator + (char c) const;
	rString& operator += (char c);

	static size_t npos;

public:

	static bool ToInt(const rString& str, int& i);

private:
	std::string m_str;
};

RECONDITE_API std::ostream& operator << (std::ostream& os, const rString& str);
RECONDITE_API std::istream& operator >> (std::istream& is, rString& str);
RECONDITE_API rString operator +(const char* cstr, const rString& rstr);


#endif
