#include "xml/rXMLDocumentLoader.hpp"

rXMLDocumentLoader::rXMLDocumentLoader(){
	m_root = NULL;
}

rXMLDocumentLoader::~rXMLDocumentLoader(){
	if (m_root)
		delete m_root;
}

rXMLElement* rXMLDocumentLoader::DetachRoot(){
	rXMLElement* root = m_root;
	m_root = NULL;
	
	return root;
}

void rXMLDocumentLoader::OnStartElement(const rString& elementName, const rXMLAttributeList& attributes){
	rXMLElement* parent = m_stack.size() ? m_stack.top() : 0;
	
	rXMLElement* element = new rXMLElement(parent, elementName);
	
	if (m_stack.size() == 0)
		m_root = element;
	
	element->AddAttributes(attributes);
	
	m_stack.push(element);
}

void rXMLDocumentLoader::OnEndElement(const rString& elementName){
	m_stack.pop();
}

void rXMLDocumentLoader::OnReadCharacters(const rString& data){
	rXMLElement* currentElement = m_stack.top();
	rString text = currentElement ->Text();
	
	text += data;
	
	currentElement->SetText(text);
}
