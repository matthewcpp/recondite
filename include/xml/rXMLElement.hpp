#ifndef R_XMLELEMENT_HPP
#define R_XMLELEMENT_HPP

#include <vector>
#include <sstream>

#include "rTypes.hpp"
#include "rString.hpp"
#include "xml/rXMLAttributeList.hpp"

class rXMLElement;
typedef std::vector<rXMLElement*> rXMLElementArray;

class rXMLElement{
public:
	rXMLElement(rXMLElement* parent, const rString& name);
	rXMLElement(rXMLElement* parent, const rString& name, const rString& text);
	rXMLElement(rXMLElement* parent, const rString& name, const rString& text, const rXMLAttributeList& attributes);
	
	~rXMLElement();

public:
	
	template<typename T>
	void AddAttribute(const rString& name, const T& value);
	
	void AddAttributes(const rXMLAttributeList& attributes);
	
	template<typename T>
	bool GetAttribute(const rString& name, T& value) const;

	bool HasAttribute(const rString& name) const;
	bool RemoveAttribute(const rString& name);
	
	rXMLElement* CreateChild(const rString& name);

	template<typename T>
	rXMLElement* CreateChild(const rString& name, const T& text);

	template<typename T>
	rXMLElement* CreateChild(const rString& name, const T& text, const rXMLAttributeList& attributes);
	
	void AddChild(rXMLElement* child);
	
	void SetName(const rString& name);
	
	template<typename T>
	void SetText(const T& text);
	
	void FindElements(const rString& search, rXMLElementArray& result) const;
	
	void ClearAttributes();
	
	rXMLElement* Parent() const;
	
	rString Text() const;

	template<typename T>
	void GetText(T& val) const;

	rString Name() const;
	
	size_t NumChildren() const;
	size_t NumAttributes() const;
	
	rXMLElement* GetChild(size_t index) const;
	rXMLElement* GetFirstChildNamed(const rString& name) const;
	
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
bool rXMLElement::GetAttribute(const rString& name, T& value) const{
	return mAttributes.GetAttributeAs<T>(name, value);
}

template<typename T>
void rXMLElement::SetText(const T& text){
	std::ostringstream s;
	s << text;
	mText = s.str().c_str();
}

template<typename T>
rXMLElement* rXMLElement::CreateChild(const rString& name, const T& text){
	std::ostringstream s;
	s << text;

	return new rXMLElement(this, name, s.str().c_str());
}

template<typename T>
rXMLElement* rXMLElement::CreateChild(const rString& name, const T& text, const rXMLAttributeList& attributes){
	std::ostringstream s;
	s << text;

	return new rXMLElement(this, name, s.str().c_str(), attributes);
}

template<typename T>
void rXMLElement::GetText(T& val) const{
	std::istringstream s (mText.c_str());
	s >> val;
}

#endif
