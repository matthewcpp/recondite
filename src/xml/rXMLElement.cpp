#include "xml/rXMLElement.hpp"

rXMLElement::rXMLElement(rXMLElement* parent, const rString& name){
	Init(parent, name, "");
}

rXMLElement::rXMLElement(rXMLElement* parent, const rString& name, const rString& text){
	Init(parent, name, text);
}

rXMLElement::rXMLElement(rXMLElement* parent, const rString& name, const rString& text, const rXMLAttributeList& attributes){
	Init(parent, name, text);
	mAttributes = attributes;
}

rXMLElement::~rXMLElement(){
	DestroyChildren();
}

void rXMLElement::Init(rXMLElement* parent, const rString& name, const rString& text){
	mParent = parent;
	
	mName = name;

	std::ostringstream s;
	s << text;

	mText = s.str().c_str();
	
	if (parent)
		parent->AddChild(this);
}

void rXMLElement::DestroyChildren(){
	for (size_t i = 0; i < mChildren.size(); i++)
		delete mChildren[i];
	
	mChildren.clear();
}

bool rXMLElement::DeleteChild(size_t index){
	rXMLElement* element = RemoveChild(index);
	
	if (!element)
		return false;
	
	delete element;
	return true;
}

bool rXMLElement::RemoveChild(rXMLElement* child){
	for (size_t i = 0; i < mChildren.size(); i++){
		if (mChildren[i] == child)
			return RemoveChild(i);
	}
	
	return false;
}

rXMLElement* rXMLElement::RemoveChild(size_t index){
	if (index >= mChildren.size())
		return NULL;
	
	rXMLElement* element = mChildren[index];
	mChildren.erase(mChildren.begin() + index);
	return element;
}

rXMLElement* rXMLElement::GetChild(size_t index) const{
	if (index >= mChildren.size())
		return NULL;
	
	return mChildren[index];
}

rXMLElement* rXMLElement::GetFirstChildNamed(const rString& name) const{
	for (size_t i= 0; i < mChildren.size(); i++){
		if (mChildren[i]->mName == name){
			return mChildren[i];
		}
			
	}
	
	return NULL;
}

rXMLElement* rXMLElement::CreateChild(const rString& name){
	return new rXMLElement(this, name);
}

void rXMLElement::AddChild(rXMLElement* child){
	rXMLElement* currentParent = child->Parent();
	
	if (currentParent != this)
		currentParent->RemoveChild(child);
	
	mChildren.push_back(child);
	
}

void rXMLElement::FindElements(const rString& search, rXMLElementArray& result) const{
	result.clear();
	
	FindElementsRec(search, result);
}

void rXMLElement::FindElementsRec(const rString& search, rXMLElementArray& result) const{
	rXMLElement* element = NULL;
	
	for (size_t i = 0; i < mChildren.size(); i++){
		element = mChildren[i];
		if (element->mName == search)
			result.push_back(element);
		
		element->FindElementsRec(search, result);
	}
}

void rXMLElement::AddAttributes(const rXMLAttributeList& attributes){
	rArrayString attributeNames;
	rString name, value;
	
	attributes.AttributeNames(attributeNames);
	
	for (size_t i = 0; i < attributeNames.size(); i++){
		name = attributeNames[i];
		attributes.GetAttributeAs<rString>(name, value);
		mAttributes.SetAttribute(name, value);
	}
}

void rXMLElement::ClearAttributes(){
	mAttributes.Clear();
}

bool rXMLElement::RemoveAttribute(const rString& name){
	return mAttributes.RemoveAttribute(name);
}

rString rXMLElement::Text() const{
	return mText;
}

size_t rXMLElement::NumChildren() const{
	return mChildren.size();
}

size_t rXMLElement::NumAttributes() const{
	return mAttributes.NumAttributes();
}

rXMLElement* rXMLElement::Parent() const{
	return mParent;
}

rString rXMLElement::Name() const{
	return mName;
}

void rXMLElement::SetName(const rString& name){
	mName = name;
}

const rXMLAttributeList& rXMLElement::Attributes() const{
	return mAttributes;
}
