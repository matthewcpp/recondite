#include "xml/rXMLAttributeList.hpp"

rXMLAttributeList::rXMLAttributeList(const rXMLAttributeList& list){
	m_attributes = list.m_attributes;
}

void rXMLAttributeList::AttributeNames(rArrayString& arr) const{
	arr.clear();
	
	for (rStringStringMap::const_iterator it = m_attributes.begin(); it != m_attributes.end(); ++it)
		arr.push_back(it->first);
}

size_t rXMLAttributeList::NumAttributes() const{
	return m_attributes.size();
}

void rXMLAttributeList::Clear(){
	m_attributes.clear();
}

size_t rXMLAttributeList::RemoveAttribute(const rString& attributeName){
	return m_attributes.erase(attributeName);
}

bool rXMLAttributeList::HasAttribute(const rString& name) const{
	return m_attributes.count(name) > 0;
}