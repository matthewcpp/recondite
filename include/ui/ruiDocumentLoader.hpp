#ifndef RUI_DOCUMENTLOADER_HPP
#define RUI_DOCUMENTLOADER_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rEngine.hpp"
#include "rPath.hpp"

#include "xml/rXMLDocument.hpp"

#include "ui/ruiDocument.hpp"


class ruiManager;

class RECONDITE_API ruiDocumentLoader{
public:
	ruiDocumentLoader(ruiManager* manager, rEngine* engine);
	
public:
	ruiDocument* LoadDocument(const rString& path, rViewport* viewport);
	
private:
	typedef void (ruiDocumentLoader::*ruiParseItemMethod)(rXMLElement* element);
	typedef std::map<rString, ruiParseItemMethod> ruiParseItemMap;
	typedef std::vector<ruiLayout*> ruiLayoutVector;

private:
	void Reset();
	ruiParseItemMethod GetParseItemMethod(const rString& itemName);

	void ParseChildItems(rXMLElement* parent);
	void ParseStylesheetItem(rXMLElement* element);
	void ParseAbsoluteLayoutItem(rXMLElement* element);
	void ParseLinearLayoutItem(rXMLElement* element);
	void ParseTextItem(rXMLElement* element);
	void ParseTextBoxItem(rXMLElement* element);
	void ParseLogTextItem(rXMLElement* element);
	void ParsePickerItem(rXMLElement* element);
	void ParseCheckboxItem(rXMLElement* element);
	void ParseButtonItem(rXMLElement* element);
	void ParseControllerItem(rXMLElement* element);
	void ParseSliderItem(rXMLElement* element);
	void ParseAnalogStick(rXMLElement* element);

	void ParseClassList(rXMLElement* element, ruiWidget* widget);
	
private:
	rEngine* m_engine;
	ruiManager* m_manager;
	
	ruiDocument* m_currentDocument;
	ruiLayoutVector m_layoutStack;

	rString m_path;
	rString m_error;

private:
	static void InitParseItemMap();
	static ruiParseItemMap s_parseItemMap;
};

#endif