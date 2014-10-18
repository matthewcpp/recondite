#include "ui/ruiStylesheetLoader.hpp"

ruiStylesheetLoader::ruiStylesheetLoader(){
	m_styleMap = NULL;
	m_currentStyle = NULL;

	InitStylePropertyTypes();
}

bool ruiStylesheetLoader::LoadStylesheet(rIStream& stream, ruiStyleMap& styleMap){
	m_styleMap = &styleMap;

	ruiStylesheetParser parser;
	parser.AddResponder(this);

	return parser.Parse(stream);
}

void ruiStylesheetLoader::StartStyle(const rString& selector){
	m_currentStyle = new ruiStyle();

	ruiStyleMap::iterator it = m_styleMap->find(selector);

	if (it != m_styleMap->end()){
		delete it->second;
	}

	m_styleMap->insert(ruiStyleMap::value_type(selector, m_currentStyle));
}

void ruiStylesheetLoader::ParseProperty(const rString& name, const rString& value){
	if (s_stylePropertyTypes.count(name)){
		rPropertyType propertyType = s_stylePropertyTypes[name];

		switch (propertyType){
			case rPROPERTY_TYPE_INT:
				LoadIntProperty(name, value);
			break;
		};
	}
}

void ruiStylesheetLoader::LoadIntProperty(const rString& name, const rString& value){
	int intVal = 0;

	if (rString::ToInt(value, intVal))
		m_currentStyle->SetInt(name, intVal);
}

void ruiStylesheetLoader::InitStylePropertyTypes(){
	if (s_stylePropertyTypes.size() >0)
		return;

	s_stylePropertyTypes["top"] = rPROPERTY_TYPE_INT;
	s_stylePropertyTypes["bottom"] = rPROPERTY_TYPE_INT;
	s_stylePropertyTypes["left"] = rPROPERTY_TYPE_INT;
	s_stylePropertyTypes["right"] = rPROPERTY_TYPE_INT;
}

ruiStylesheetLoader::rStylePropertyTypeMap ruiStylesheetLoader::s_stylePropertyTypes;
