#include "ui/ruiStylesheetLoader.hpp"

ruiStylesheetLoader::ruiParseStyleMap ruiStylesheetLoader::s_parseStyleMap;

ruiStylesheetLoader::ruiStylesheetLoader(){
	m_styleMap = NULL;
	m_currentStyle = NULL;

	InitParseStyleMap();
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
		m_styleMap->erase(it);
	}

	m_styleMap->insert(ruiStyleMap::value_type(selector, m_currentStyle));
}

ruiStylesheetLoader::ruiParseStyleMethod ruiStylesheetLoader::GetParseStyleMethod(const rString& name){
	rString propertyName = name;

	for (size_t i = 0; i < propertyName.size(); i++)
		propertyName[i] = tolower(propertyName[i]);

	if (s_parseStyleMap.count(propertyName))
		return s_parseStyleMap[propertyName];
	else
		return NULL;
}

void ruiStylesheetLoader::ParseProperty(const rString& name, const rString& value){
	ruiParseStyleMethod method = GetParseStyleMethod(name);

	if (method)
		(*this.*method)(name, value);
}

void ruiStylesheetLoader::ParseIntProperty(const rString& name, const rString& value){
	int intVal = 0;

	if (rString::ToInt(value, intVal))
		m_currentStyle->SetInt(name, intVal);
}

void ruiStylesheetLoader::ParseColorProperty(const rString& name, const rString& value){
	int r,g,b,a;

	if (sscanf(value.c_str(), "%i %i %i %i", &r, &g, &b, &a) == 4){
		m_currentStyle->SetColor(name, rColor(r,g,b,a));
	}
}

void ruiStylesheetLoader::ParseStringProperty(const rString& name, const rString& value){
	m_currentStyle->SetString(name, value);
}

void ruiStylesheetLoader::ParseMarginProperty(const rString& name, const rString& value){
	int marginVal;
	if (rString::ToInt(value, marginVal)){
		m_currentStyle->SetInt("margin-top", marginVal);
		m_currentStyle->SetInt("margin-bottom", marginVal);
		m_currentStyle->SetInt("margin-left", marginVal);
		m_currentStyle->SetInt("margin-right", marginVal);
	}
}

void ruiStylesheetLoader::InitParseStyleMap(){
	if (s_parseStyleMap.size() >0)
		return;

	s_parseStyleMap["top"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["bottom"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["left"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["right"] = &ruiStylesheetLoader::ParseIntProperty;


	s_parseStyleMap["padding-top"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["padding-bottom"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["padding-left"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["padding-right"] = &ruiStylesheetLoader::ParseIntProperty;

	s_parseStyleMap["margin-top"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["margin-bottom"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["margin-left"] = &ruiStylesheetLoader::ParseIntProperty;
	s_parseStyleMap["margin-right"] = &ruiStylesheetLoader::ParseIntProperty;

	s_parseStyleMap["margin"] = &ruiStylesheetLoader::ParseMarginProperty;

	s_parseStyleMap["border-radius"] = &ruiStylesheetLoader::ParseIntProperty;

	s_parseStyleMap["color"] = &ruiStylesheetLoader::ParseColorProperty;
	s_parseStyleMap["background-color"] = &ruiStylesheetLoader::ParseColorProperty;
	s_parseStyleMap["border-color"] = &ruiStylesheetLoader::ParseColorProperty;

	s_parseStyleMap["font"] = &ruiStylesheetLoader::ParseStringProperty;
}
