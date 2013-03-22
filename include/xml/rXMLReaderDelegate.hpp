#ifndef R_XML_READER_DELEGATE_HPP
#define R_XML_READER_DELEGATE_HPP

#include <string>

#include "xml/rXMLAttributeList.hpp"

class rXMLReaderDelegate{
public:
    virtual void OnBeginParseDocument(){}
    virtual void OnEndParseDocument(){}
    virtual void OnStartElement(const rString& elementName, const rXMLAttributeList& attributes){}
    virtual void OnEndElement(const rString& elementName){}
    virtual void OnComment(const rString& comment){}
    virtual void OnReadCharacters(const rString& data){}
    virtual void OnReadCDATA(const rString& data){}
    virtual void OnParseError(int errorNum , int lineNumber){}
    virtual ~rXMLReaderDelegate(){}
};

#endif
