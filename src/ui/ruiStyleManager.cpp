#include "ui/ruiStyleManager.hpp"

ruiStyleManager::ruiStyleManager(){

}

ruiStyleManager::~ruiStyleManager(){
	Clear();
}

ruiStyle* ruiStyleManager::CreateStyle(const rString& selector){
	if (m_styles.count(selector)){
		return NULL;
	}
	else{
		ruiStyle* style = new ruiStyle();
		m_styles[selector] = style;
		return style;
	}
}

ruiStyle* ruiStyleManager::GetStyle(const rString& selector) const{
	ruiStyleMap::const_iterator result = m_styles.find(selector);

	if (result == m_styles.end())
		return NULL;
	else
		return result->second;
}

size_t ruiStyleManager::StyleCount() const{
	return m_styles.size();
}

bool ruiStyleManager::ParseStylesheet(std::istream& stream){
	rXMLDocument document;
	document.LoadFromStream(stream);
	
	rXMLElement* root = document.GetRoot();
	
	for (size_t i = 0; i < root->NumChildren(); i++){
		rXMLElement* styleElement = root->GetChild(i);
		rString selector;

		styleElement->GetAttribute<rString>("selector", selector);
		ruiStyle* style = CreateStyle(selector);

		for (size_t p = 0; p < styleElement->NumChildren(); p++){
			rXMLElement* prop = styleElement->GetChild(p);
			rString name = prop->Name();

			rPropertyValue propertyValue;
			int propertyType;
			prop->GetAttribute<int>("type", propertyType);
			
			switch (propertyType)
			{
			case rPROPERTY_TYPE_BOOL:
				prop->GetText<bool>(propertyValue.boolVal);
				style->SetBool(name, propertyValue.boolVal);
				break;
			case rPROPERTY_TYPE_INT:
				prop->GetText<int>(propertyValue.intVal);
				style->SetInt(name, propertyValue.intVal);
				break;
			case rPROPERTY_TYPE_FLOAT:
				prop->GetText<float>(propertyValue.floatVal);
				style->SetInt(name, propertyValue.floatVal);
				break;
			case rPROPERTY_TYPE_STRING:{
				rString str = prop->Text();
				style->SetString(name, str);
			}
				break;
			case rPROPERTY_TYPE_COLOR:{
				rString str = prop->Text();
				rIStringStream stream(str);
				rColor color;

				stream >> color.red >> color.green >> color.blue >> color.alpha;
				style->SetColor(name, color);
			}
				break;
			case rPROPERTY_TYPE_FONT:
				break;
			case rPROPERTY_TYPE_TEXTURE:
				break;
			default:
				break;
			}
		}
	}
	

	return true;
}

void ruiStyleManager::Clear(){
	ruiStyleMap::iterator end = m_styles.end();

	for (ruiStyleMap::iterator it = m_styles.begin(); it != end; ++it)
		delete it->second;

	m_styles.clear();
}