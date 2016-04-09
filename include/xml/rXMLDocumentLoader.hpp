#ifndef R_XMLDOCUMENTLOADER_HPP
#define R_XMLDOCUMENTLOADER_HPP

#include <stack>

#include "xml/rXMLReader.hpp"
#include "xml/rXMLReaderDelegate.hpp"
#include "xml/rXMLElement.hpp"

class rXMLDocumentLoader : public rXMLReaderDelegate{
public:
	rXMLDocumentLoader();
	~rXMLDocumentLoader();
	
	rXMLElement* DetachRoot();
	
	virtual void OnStartElement(const rString& elementName, const rXMLAttributeList& attributes);
	virtual void OnEndElement(const rString& elementName);
	virtual void OnReadCharacters(const rString& data);
	
private:
	typedef std::stack<rXMLElement*> rXMLElementStack;

private:
	rXMLElementStack m_stack;
	rXMLElement* m_root;
	rXMLReaderError m_error;
};

#endif
