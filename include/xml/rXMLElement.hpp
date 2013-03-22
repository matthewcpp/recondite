#ifndef R_XMLELEMENT_HPP
#define R_XMLELEMENT_HPP

#include <vector>

#include "rTypes.hpp"
#include "rXMLAttributeList.hpp"

class rXMLElement;
typedef std::vector<rXMLElement*> rXMLElementArray;

class rXMLElement{
public:
	rXMLElement(rXMLElement* parent, const rString& name, const rString& text = "");
	rXMLElement(rXMLElement* parent, const rString& name, const rString& text, const rXMLAttributeList& attributes);
	~rXMLElement();
	
	template<typename T>
	void AddAttribute(const rString& name, const T& value);
	
	void AddAttributes(const rXMLAttributeList& attributes);
	
	template<typename T>
	bool GetAttribute(const rString& name, const T& value) const;
	
	bool RemoveAttribute(const rString& name);
	
	rXMLElement* CreateChild(const rString& name, const rString& text = "");
	rXMLElement* CreateChild(const rString& name, const rString& text, const rXMLAttributeList& attributes);
	void AddChild(rXMLElement* child);
	
	void SetName(const rString& name);
	void SetText(const rString& text);
	
	void FindElements(const rString& search, rXMLElementArray& result) const;
	
	void ClearAttributes();
	
	rXMLElement* Parent() const;
	
	rString Text() const;
	rString Name() const;
	
	size_t NumChildren() const;
	size_t NumAttributes() const;
	
	rXMLElement* GetChild(size_t index) const;
	
	void DestroyChildren();
	
	bool DeleteChild(size_t index);
	
	const rXMLAttributeList& Attributes() const;
	
private:
	void Init(rXMLElement* parent, const rString& name, const rString& text);
	void FindElementsRec(const rString& search, rXMLElementArray& result) const;
	bool RemoveChild(rXMLElement* child);
	rXMLElement* RemoveChild(size_t index);

private:
	
	rXMLElement* mParent;
	
	rXMLElementArray mChildren;
	rXMLAttributeList mAttributes;
	
	rString mName;
	rString mText;
};

template<typename T>
void rXMLElement::AddAttribute(const rString& name, const T& value){
	mAttributes.SetAttribute<T>(name, value);
}

template<typename T>
bool rXMLElement::GetAttribute(const rString& name, const T& value) const{
	return mAttributes.GetAttributeAs<T>(name, value);
}

#endif
