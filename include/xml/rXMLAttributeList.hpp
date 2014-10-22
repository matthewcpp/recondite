#ifndef R_ATTRIBUTE_LIST_HPP
#define R_ATTRIBUTE_LIST_HPP

#include <map>
#include <string>
#include <sstream>

#include "rTypes.hpp"



class rXMLAttributeList{
public:
	rXMLAttributeList(){}
	rXMLAttributeList(const rXMLAttributeList& list);
	
	template <typename T>
	void SetAttribute(const rString& name , const T& value);
	
	template <typename T>
	bool GetAttributeAs(const rString& name , T& value) const;
	
	size_t RemoveAttribute(const rString& attributeName);
	void AttributeNames(rArrayString& arr) const;
	bool HasAttribute(const rString& name) const;
	
	size_t NumAttributes() const;
	void Clear();
	
private:
	rStringStringMap m_attributes;
};


template <typename T>
void rXMLAttributeList::SetAttribute(const rString& name , const T& value){
	std::ostringstream str;
	str << value;
	
	m_attributes[name] = str.str().c_str();
}

template <typename T>
bool rXMLAttributeList::GetAttributeAs(const rString& name , T& value) const{
	rStringStringMap::const_iterator it = m_attributes.find(name);
	
	if (it == m_attributes.end())
		return false;
	
	std::istringstream str(it->second.c_str());
	str >> value;
	
	return true;
}


#endif
