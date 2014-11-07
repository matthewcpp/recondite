#ifndef R_XMLUTIL_HPP
#define R_XMLUTIL_HPP

#include "xml/rXMLElement.hpp"

#include "rVector3.hpp"
#include "rAlignedBox3.hpp"
#include "rColor.hpp"

namespace rXMLUtil{
	rXMLElement* CreateVector3Element(rXMLElement* parent, const rString& name, const rVector3& v);
	rXMLElement* CreateColorElement(rXMLElement* parent, const rString& name, const rColor& c);
	rXMLElement* CreateAlignedBox3Element(rXMLElement* parent, const rString& name, const rAlignedBox3& box);

	bool ReadVector3FromElement(rXMLElement* element, rVector3& v);
	void ReadColorFromElement(rXMLElement* element, rColor& c);
	void ReadAlignedBox3FromFromElement(rXMLElement* element, rAlignedBox3& box);
}

#endif