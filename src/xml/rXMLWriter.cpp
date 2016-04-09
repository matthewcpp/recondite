#include "xml/rXMLWriter.hpp"

rXMLWriter::~rXMLWriter(){
	CloseAllElements();
}

void rXMLWriter::CloseAllElements(){
	while(m_stack.size() > 0)
		CloseCurrentElement();
}

void rXMLWriter::WriteAttribute(const rString& attrName , const rString& value){
	m_stream << attrName << "='" << value << "'";
}

void rXMLWriter::WriteStartElementTag(const rString& name){
	m_stream << '<'<<name<< '>';
}

void rXMLWriter::WriteEndElementTag(const rString& name){
	m_stream << "</" << name<<">\n";
} 

void rXMLWriter::WriteElement(const rString& name){
	Indent();
	m_stream << '<'<<name<< " />";
}


void rXMLWriter::WriteOpenElement(const rString& name){
	WriteStartElementTag(name);
	m_stack.push(name);
}

void rXMLWriter::Indent(){
	for (size_t i =0; i < m_stack.size(); i++)
		m_stream << '\t';
}

void rXMLWriter::CloseCurrentElement(){
	if (m_stack.size() == 0)
		return;
	
	rString tag = m_stack.top();
	m_stack.pop();
	
	Indent();
	WriteEndElementTag(tag);
	
}

rString rXMLWriter::CurrentOpenElement() const{
	if (m_stack.size() == 0)
		return "";
	
	return m_stack.top();
}

void rXMLWriter::WriteAttributeList(const rXMLAttributeList& attributes){
	rArrayString attr;
	rString val;
	
	attributes.AttributeNames(attr);
	for (size_t i = 0; i < attr.size(); i++){
		attributes.GetAttributeAs<rString>(attr[i] , val);
		if (i)
			m_stream << ' ';
		
		WriteAttribute(attr[i] , val);	
	}
}


void rXMLWriter::WriteElementWithAttributes(const rString& name , const rXMLAttributeList& attributes){
	Indent();
	
	m_stream << '<'<<name<<' ';
	WriteAttributeList(attributes);
	m_stream << " />" << '\n';
}

void rXMLWriter::WriteOpenElementWithAttributes(const rString& name , const rXMLAttributeList& attributes){	
	Indent();
	
	m_stream << '<'<<name<<' ';
	WriteAttributeList(attributes);
	m_stream << " >" << '\n';
	
	m_stack.push(name);
}
