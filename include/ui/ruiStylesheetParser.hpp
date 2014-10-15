#ifndef RUI_STYLESHEETPARSER_HPP
#define RUI_STYLESHEETPARSER_HPP

#include <cctype>
#include <vector>

#include "rBuild.hpp"
#include "rString.hpp"
#include "stream/rIStream.hpp"

class RECONDITE_API ruiStyleSheetParserResponder {
public:
	virtual void StartStyle(const rString& selector) {}
	virtual void EndStyle(const rString& selector) {}
	virtual void ParseProperty(const rString& name, const rString& value) {}
	virtual void Error(int lineNum, const rString& errorString) {}
	virtual void Warning(int lineNum, const rString& warningString) {}
};

class RECONDITE_API ruiStylesheetParser {
public:
	ruiStylesheetParser();

	bool Parse(rIStream& stream);
	void Reset();

	void AddResponder(ruiStyleSheetParserResponder* responder);

private:
	void ParseChar(int ch);

	bool ParseSelector(int ch);
	bool ParseOpenBrace(int ch);
	bool ParsePropName(int ch);
	bool ParseColon(int ch);
	bool ParsePropVal(int ch);
	bool ParseSemicolon(int ch);
	bool ParseNextProperty(int ch);

private:
	void TriggerStartStyle();
	void TriggerEndStyle();
	void TriggerParseProperty();
	void TriggerError(const rString& errorString);
	void TriggerWarning(const rString& errorString);

private:
	enum ParserState{
		PARSING_SELECTOR,
		PARSING_OPEN_BRACE,
		PARSING_PROPNAME,
		PARSING_COLON,
		PARSING_PROPVAL,
		PARSING_SEMICOLON,
		PARSING_PARSING_NEXT_PROPERTY
	};

	typedef std::vector<ruiStyleSheetParserResponder*> ruiStyleSheetParserResponderVector;

private:
	ParserState m_state;
	int m_lineNumber;

	rString m_currentSelector;
	rString m_currentPropName;
	rString m_currentPropValue;
	
	ruiStyleSheetParserResponderVector m_responders;
};

#endif