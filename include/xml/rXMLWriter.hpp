#ifndef R_XMLWRITER_HPP
#define R_XMLWRITER_HPP

#include <string>
#include <stack>
#include <sstream>
#include <ostream>

#include "rTypes.hpp"
#include "xml/rXMLAttributeList.hpp"


class rXMLWriter{
public:
	rXMLWriter(std::ostream& stream) : m_stream(stream) {}
	~rXMLWriter();
	
public:

	void WriteElement(const rString& name);
	void WriteOpenElement(const rString& name);
	
	template<typename T>
	void WriteValue(const T& value);
	
	template <typename T>
	void WriteElementWithAttribute(const rString& name , const rString& attrName , const T& attrValue);
	
	template <typename T>
	void WriteOpenElementWithAttribute(const rString& name , const rString& attrName , const T& attrValue);
	
	template <typename T>
	void WriteElementWithValue(const rString& name , const T& value);
	
	template <typename T>
	void WriteOpenElementWithValue(const rString& name , const T& value);
	
	template <typename T, typename V>
	void WriteElementWithAttributeAndValue(const rString& name , const rString& attrName , const T& attrValue, const V& value);
	
	template <typename T, typename V>
	void WriteOpenElementWithAttributeAndValue(const rString& name , const rString& attrName , const T& attrValue, const V& value);
	
	void WriteElementWithAttributes(const rString& name , const rXMLAttributeList& attributes);
	void WriteOpenElementWithAttributes(const rString& name , const rXMLAttributeList& attributes);
	
	template <typename T>
	void WriteElementWithAttributesAndValue(const rString& name , const rXMLAttributeList& attributes, const T& value);
	
	template <typename T>
	void WriteOpenElementWithAttributesAndValue(const rString& name , const rXMLAttributeList& attributes, const T& value);
	
	
	void CloseCurrentElement();
	void CloseAllElements();
	rString CurrentOpenElement() const;

	
private:

	void WriteStartElementTag(const rString& name);
	void WriteEndElementTag(const rString& name);
	
	void WriteAttributeList(const rXMLAttributeList& attributes);
	void WriteAttribute(const rString& attrName , const rString& value);
	
	template <typename T>
	void WriteStartElementTagWithAttribute(const rString& name , const rString& attrName , const T& attrValue);
	
	void Indent();
	
	typedef std::stack<rString> rElementStack;
	
private:
	std::ostream& m_stream;
	rElementStack m_stack;
};

template <typename T>
void rXMLWriter::WriteValue(const T& value){
	if (m_stack.size() == 0)
		return;
	
	std::ostringstream str;
	str << value;
	
	Indent();
	
	m_stream << str.str() << std::endl;
	
}

template <typename T>
void rXMLWriter::WriteStartElementTagWithAttribute(const rString& name , const rString& attrName , const T& attrValue){
	std::ostringstream str;
	str << attrValue;
	
	m_stream << '<'<<name << ' ';
	WriteAttribute(attrName , str.str());
	m_stream <<">";
}

template <typename T>
void rXMLWriter::WriteElementWithValue(const rString& name , const T& value){
	std::ostringstream str;
	str << value;
	
	Indent();
	
	WriteStartElementTag(name);
	m_stream << str.str();
	WriteEndElementTag(name);
	
}

template <typename T>
void rXMLWriter::WriteOpenElementWithValue(const rString& name , const T& value){
	std::ostringstream str;
	str << value;
	
	Indent();
	
	WriteStartElementTag(name);
	m_stream << str.str() << std::endl;

	m_stack.push(name);	
}


template <typename T>
void rXMLWriter::WriteOpenElementWithAttribute(const rString& name , const rString& attrName , const T& attrValue){
	std::ostringstream str;
	str << attrValue;
	
	Indent();
	
	WriteStartElementTagWithAttribute(name , attrName , str.str());
	m_stream << std::endl;
	
	m_stack.push(name);
}

template <typename T>
void rXMLWriter::WriteElementWithAttribute(const rString& name , const rString& attrName , const T& attrValue){
	std::ostringstream str;
	str << attrValue;
	
	Indent();
	
	m_stream << '<' << name << ' ';
	WriteAttribute(attrName , str.str());
	m_stream << " />"<<std::endl;
}

template <typename T, typename V>
void rXMLWriter::WriteElementWithAttributeAndValue(const rString& name , const rString& attrName , const T& attrValue, const V& value){
	std::ostringstream str;
	str << value;
		
	Indent();
	
	WriteStartElementTagWithAttribute<T>(name , attrName , attrValue);
	m_stream << str.str();
	WriteEndElementTag(name);
}

template <typename T, typename V>
void rXMLWriter::WriteOpenElementWithAttributeAndValue(const rString& name , const rString& attrName , const T& attrValue, const V& value){
	std::ostringstream str;
	str << value;
		
	Indent();
	
	WriteStartElementTagWithAttribute<T>(name , attrName , attrValue);
	m_stream << str.str()<<std::endl;
	
	m_stack.push(name);
}

template <typename T>
void rXMLWriter::WriteElementWithAttributesAndValue(const rString& name , const rXMLAttributeList& attributes, const T& value){
	std::ostringstream str;
	str << value;
	
	Indent();
	
	m_stream << '<' << name;
	
	if (attributes.NumAttributes() > 0){
		m_stream << ' ';
		WriteAttributeList(attributes);
	}
	
	m_stream << ">"<< str.str();
	
	WriteEndElementTag(name);
}

template <typename T>
void rXMLWriter::WriteOpenElementWithAttributesAndValue(const rString& name , const rXMLAttributeList& attributes, const T& value){
	std::ostringstream str;
	str << value;
	
	Indent();
	
	m_stream << '<' << name;
	
	if (attributes.NumAttributes() > 0){
		m_stream << ' ';
		WriteAttributeList(attributes);
	}
	
	m_stream << ">"<<str.str()<<std::endl;
	
	m_stack.push(name);
}
	


#endif
