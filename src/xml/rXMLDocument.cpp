#include "xml/rXMLDocument.hpp"

rXMLDocument::rXMLDocument(){
	m_root = NULL;
}

rXMLDocument::~rXMLDocument(){
	Clear();
}

void rXMLDocument::Clear(){
	if (m_root)
		delete m_root;
	
	m_root = NULL;
}

rXMLElement* rXMLDocument::GetRoot() const{
	return m_root;
}

rXMLElement* rXMLDocument::CreateRoot(const rString& name){
	Clear();
	
	m_root = new rXMLElement(NULL, name);
	
	return m_root;
}

int rXMLDocument::WriteToFile(const rString& path) const{
	std::ofstream file(path.c_str());
	
	if (!file)
		return 1;
	
	int error = WriteToStream(file);
	
	file.close();
	return error;
}

int rXMLDocument::WriteToStream(std::ostream& stream) const{
	if (m_root){
		rXMLWriter writer(stream);
		WriteXMLElement(m_root, writer);
	}
	return 0;
}

void rXMLDocument::WriteXMLElement(const rXMLElement* element, rXMLWriter& writer) const{
	size_t numChildren = element->NumChildren(); 
	if (numChildren){
		writer.WriteOpenElementWithAttributesAndValue<rString>(element->Name(), element->Attributes(), element->Text());
		
		for (size_t i = 0; i < numChildren; i++){
			WriteXMLElement(element->GetChild(i), writer);
		}
		
		writer.CloseCurrentElement();
	}
	else{
		writer.WriteElementWithAttributesAndValue<rString>(element->Name(), element->Attributes(), element->Text());
	}
}
