#ifndef R_XMLDOCUMENT_HPP
#define R_XMLDOCUMENT_HPP

#include <fstream>

#include "rTypes.hpp"
#include "rXMLElement.hpp"

#include "rXMLWriter.hpp"

class rXMLDocument{
public:
	rXMLDocument();
	~rXMLDocument();
	
	void Clear();
	rXMLElement* GetRoot() const;
	rXMLElement* CreateRoot(const rString& name);
	
	int WriteToFile(const rString& path) const;
	int WriteToStream(std::ostream& stream) const;
	
private:
	
	void WriteXMLElement(const rXMLElement* element, rXMLWriter& writer) const;
	
private:
	
	rXMLElement* m_root;
};

#endif
