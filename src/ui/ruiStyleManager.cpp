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

bool ruiStyleManager::ParseStylesheet(rIStream& stream){
	ruiStylesheetLoader loader;
	loader.LoadStylesheet(stream, m_styles);

	return true;
}

void ruiStyleManager::Clear(){
	ruiStyleMap::iterator end = m_styles.end();

	for (ruiStyleMap::iterator it = m_styles.begin(); it != end; ++it)
		delete it->second;

	m_styles.clear();
}