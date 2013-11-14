#ifndef R_XMLUTIL_HPP
#define R_XMLUTIL_HPP

#include "xml/rXMLElement.hpp"

#include "rVector3.hpp"
#include "rAlignedBox3.hpp"

namespace rXMLUtil{
	rXMLElement* CreateVector3Element(rXMLElement* parent, const rString& name, const rVector3& v);
	rXMLElement* CreateAlignedBox3Element(rXMLElement* parent, const rString& name, const rAlignedBox3& box);

	void ReadVector3FromElement(rXMLElement* element, rVector3& v);
	void ReadAlignedBox3FromFromElement(rXMLElement* element, rAlignedBox3& box);
}

#endif