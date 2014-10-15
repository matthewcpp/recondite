#include "ruiStylesheetParser.hpp"

ruiStylesheetParser::ruiStylesheetParser(){
	m_state = PARSING_SELECTOR;
}

void ruiStylesheetParser::Reset(){
	m_state = PARSING_SELECTOR;
	m_lineNumber = 0;

	m_currentSelector.clear();
	m_currentPropName.clear();
	m_currentPropValue.clear();
}

void ruiStylesheetParser::TriggerStartStyle(){
	for (size_t i = 0; i < m_responders.size(); i++)
		m_responders[i]->StartStyle(m_currentSelector);
}

void ruiStylesheetParser::TriggerEndStyle(){
	for (size_t i = 0; i < m_responders.size(); i++)
		m_responders[i]->EndStyle(m_currentSelector);

	m_currentSelector.clear();
}

void ruiStylesheetParser::TriggerParseProperty(){
	for (size_t i = 0; i < m_responders.size(); i++)
		m_responders[i]->ParseProperty(m_currentPropName, m_currentPropValue);

	m_currentPropName.clear();
	m_currentPropValue.clear();
}

void ruiStylesheetParser::TriggerError(const rString& errorString){
	for (size_t i = 0; i < m_responders.size(); i++)
		m_responders[i]->Error(m_lineNumber, errorString);
}

void ruiStylesheetParser::TriggerWarning(const rString& errorString){
	for (size_t i = 0; i < m_responders.size(); i++)
		m_responders[i]->Warning(m_lineNumber, errorString);
}

void ruiStylesheetParser::AddResponder(ruiStyleSheetParserResponder* responder){
	m_responders.push_back(responder);
}

bool ruiStylesheetParser::Parse(rIStream& stream){
	Reset();
	char ch;

	while (stream.get(ch)){
		switch (m_state){

			case PARSING_SELECTOR:
				ParseSelector(ch);
				break;
			case PARSING_OPEN_BRACE:
				ParseOpenBrace(ch);
				break;
			case PARSING_PROPNAME:
				ParsePropName(ch);
				break;
			case PARSING_COLON:
				ParseColon(ch);
				break;
			case PARSING_PROPVAL:
				ParsePropVal(ch);
				break;
			case PARSING_SEMICOLON:
				ParsePropVal(ch);
				break;
			case PARSING_PARSING_NEXT_PROPERTY:
				ParseNextProperty(ch);
				break;
		};
	}

	return m_state == PARSING_SELECTOR;
}

bool ruiStylesheetParser::ParseSelector(int ch){
	if (m_currentSelector.empty()){
		if (isspace(ch)){
			return true;
		}
		else if (isalpha(ch) || ch == '.'){
			m_currentSelector += (char)ch;
			return true;
		}
	}
	else {
		if ( ch == '{'){
			TriggerStartStyle();
			m_state = PARSING_PROPNAME;
			return true;
		}
		else if ( isspace(ch)){
			m_state = PARSING_OPEN_BRACE;
			return true;
		}
		else if (isalpha(ch)){
			m_currentSelector += (char)ch;
			return true;
		}
	}

	return false;
}

bool ruiStylesheetParser::ParseOpenBrace(int ch){
	if (ch == '{'){
		TriggerStartStyle();
		m_state = PARSING_PROPNAME;
		return true;
	}
	else if (isspace(ch)){
		return true;
	}
	else{
		TriggerError("ParseOpenBrace: Unexpected character");
		return false;
	}
}
bool ruiStylesheetParser::ParsePropName(int ch){
	if (m_currentPropName.empty()){
		if (isspace(ch)){
			return true;
		}
		else if (isalpha(ch)){
			m_currentPropName += (char)ch;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if (isspace(ch)){
			m_state = PARSING_COLON;
			return true;
		}
		else if (ch == ':'){
			m_state = PARSING_PROPVAL;
			return true;
		}
		else if (isalnum  (ch) || ch == '_' || ch == '-'){
			m_currentPropName += (char)ch;
			return true;
		}
		else{
			return false;
		}

	}
}

bool ruiStylesheetParser::ParseColon(int ch){
	if (ch == ':'){
		m_state = PARSING_PROPVAL;
		return true;
	}
	else if (isspace(ch)){
		return true;
	}
	else{
		TriggerError("ParseColon: Unexpected character");
		return false;
	}
}

bool ruiStylesheetParser::ParsePropVal(int ch){
	if (m_currentPropValue.empty()){
		if (isspace(ch)){
			return true;
		}
	}
	else {
		if ( ch == ';'){
			m_state = PARSING_PARSING_NEXT_PROPERTY;
			TriggerParseProperty();
			return true;
		}
	}

	if (isprint (ch)){
		m_currentPropValue += (char)ch;
		return true;
	}

	return false;
}

bool ruiStylesheetParser::ParseSemicolon(int ch){
	if (ch == ';'){
		m_state = PARSING_PARSING_NEXT_PROPERTY;
		TriggerParseProperty();
		return true;
	}
	else if (isspace(ch)){
		return true;
	}
	else{
		TriggerError("ParseSemicolon: Unexpected character");
		return false;
	}
}

bool ruiStylesheetParser::ParseNextProperty(int ch){
	if (isspace(ch)){
		return true;
	}
	else if (ch == '}'){
		TriggerEndStyle();

		m_state = PARSING_SELECTOR;
	}
	else if (isalpha(ch)){
		m_state = PARSING_PROPNAME;
		m_currentPropName += (char)ch;
		return true;
	}
	else {
		return false;
	}
}