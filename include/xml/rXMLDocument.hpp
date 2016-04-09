#ifndef R_XMLDOCUMENT_HPP
#define R_XMLDOCUMENT_HPP

#include "rBuild.hpp"

#include "rTypes.hpp"
#include "xml/rXMLElement.hpp"

#include "xml/rXMLWriter.hpp"
#include "xml/rXMLReader.hpp"
#include "xml/rXMLDocumentLoader.hpp"

#include "stream/rIFileStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rXMLDocument{
public:
	rXMLDocument();
	~rXMLDocument();
	
	void Clear();
	rXMLElement* GetRoot() const;
	rXMLElement* CreateRoot(const rString& name);
	
	void FindElements(const rString& search, rXMLElementArray& result) const;
	
	int WriteToStream(rOStream& stream) const;
	
	rXMLReaderError LoadFromFile(const rString& path);
	rXMLReaderError LoadFromStream(rIStream& stream);
	
private:
	
	void WriteXMLElement(const rXMLElement* element, rXMLWriter& writer) const;
	
private:
	
	rXMLElement* m_root;
};

#endif
