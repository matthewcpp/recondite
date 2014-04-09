#include "rArrayString.hpp"

const rString& rArrayString::operator[](int index) const{
	return m_array[index];
}

rString& rArrayString::operator[](int index){
	return m_array[index];
}

void rArrayString::push_back(const rString& str){
	m_array.push_back(str);
}

size_t rArrayString::size() const{
	return m_array.size();
}

void rArrayString::clear(){
	m_array.clear();
}