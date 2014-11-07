#include "xml/rXMLUtil.hpp"

rXMLElement* rXMLUtil::CreateVector3Element(rXMLElement* parent, const rString& name, const rVector3& v){
	rXMLElement* element = parent->CreateChild(name);

	element->AddAttribute("x", v.x);
	element->AddAttribute("y", v.y);
	element->AddAttribute("z", v.z);

	return element;
}

rXMLElement* rXMLUtil::CreateAlignedBox3Element(rXMLElement* parent, const rString& name, const rAlignedBox3& box){
	rXMLElement* element = parent->CreateChild(name);

	CreateVector3Element(element, "min", box.min);
	CreateVector3Element(element, "max", box.max);

	return element;
}

rXMLElement* rXMLUtil::CreateColorElement(rXMLElement* parent, const rString& name, const rColor& c){
	rXMLElement* element = parent->CreateChild(name);

	element->AddAttribute("r", (int)c.red);
	element->AddAttribute("g", (int)c.green);
	element->AddAttribute("b", (int)c.blue);
	element->AddAttribute("a", (int)c.alpha);

	return element;
}

bool rXMLUtil::ReadVector3FromElement(rXMLElement* element, rVector3& v){
	if (element){
		element->GetAttribute<float>("x", v.x);
		element->GetAttribute<float>("y", v.y);
		element->GetAttribute<float>("z", v.z);
		return true;
	}

	return false;
}

void rXMLUtil::ReadAlignedBox3FromFromElement(rXMLElement* element, rAlignedBox3& box){
	if (element){
		ReadVector3FromElement(element->GetFirstChildNamed("min"), box.min);
		ReadVector3FromElement(element->GetFirstChildNamed("max"), box.max);
	}
}

void rXMLUtil::ReadColorFromElement(rXMLElement* element, rColor& c){
	if (element){
		unsigned int r,g,b,a;
		element->GetAttribute<unsigned int>("r", r);
		element->GetAttribute<unsigned int>("g", g);
		element->GetAttribute<unsigned int>("b", b);
		element->GetAttribute<unsigned int>("a", a);

		c.Set((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);
	}
}