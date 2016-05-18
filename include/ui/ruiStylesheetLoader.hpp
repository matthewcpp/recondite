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
	typedef void (ruiStylesheetLoader::*ruiParseStyleMethod)(const rString& name, const rString& value);
	typedef std::map<rString, ruiParseStyleMethod> ruiParseStyleMap;

private:
	ruiParseStyleMethod GetParseStyleMethod(const rString& name);

	void ParseIntProperty(const rString& name, const rString& value);
	void ParseColorProperty(const rString& name, const rString& value);
	void ParseStringProperty(const rString& name, const rString& value);

	void ParseMarginProperty(const rString& name, const rString& value);
	void ParsePaddingProperty(const rString& name, const rString& value);

private:
	ruiStyleMap* m_styleMap;
	ruiStyle* m_currentStyle;

private:
	static void InitParseStyleMap();
	static ruiParseStyleMap s_parseStyleMap;
};

#endif