#ifndef RUI_STYLESHEETLOADER_HPP
#define RUI_STYLESHEETLOADER_HPP

#include <map>

#include "rBuild.hpp"

#include "ruiStyle.hpp"
#include "stream/rIStream.hpp"
#include "ui/ruiStylesheetParser.hpp"

class RECONDITE_API ruiStylesheetLoader : public ruiStyleSheetParserResponder{
public:
	ruiStylesheetLoader();
	bool LoadStylesheet(rIStream& stream, ruiStyleMap& styleMap);

public:
	virtual void StartStyle(const rString& selector);
	virtual void ParseProperty(const rString& name, const rString& value);

private:
	void LoadIntProperty(const rString& name, const rString& value);
	void LoadColorProperty(const rString& name, const rString& value);

private:
	typedef std::map <rString, rPropertyType> rStylePropertyTypeMap;

private:
	ruiStyleMap* m_styleMap;
	ruiStyle* m_currentStyle;

private:
	static void InitStylePropertyTypes();
	static rStylePropertyTypeMap s_stylePropertyTypes;
};

#endif