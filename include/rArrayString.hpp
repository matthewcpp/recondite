#ifndef R_ARRAYSTRING_HPP
#define R_ARRAYSTRING_HPP

#include <vector>

#include "rString.hpp"

class RECONDITE_API rArrayString{
public:
	const rString& operator[](int index) const;
	rString& operator[](int index);

	void push_back(const rString& str);
	size_t size() const;
	void clear();

private:
	std::vector<rString> m_array;
};

#endif