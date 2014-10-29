#ifndef R_XML_READER_HPP
#define R_XML_READER_HPP

#include <sstream>
#include <fstream>
#include <stack>

#include "rTypes.hpp"
#include "rString.hpp"
#include "stream/rIFileStream.hpp"

#include "xml/rXMLReaderDelegate.hpp"
#include "xml/rXMLAttributeList.hpp"

#define rXML_SPACE ' '
#define rXML_QUOTE '"'
#define rXML_APOS '\''
#define rXML_TAB '\t'
#define rXML_EQUALS '='
#define rXML_TAG_BEGIN '<'
#define rXML_TAG_END '>'
#define rXML_TAG_CLOSE '/'
#define rXML_COMMENT_TAG_BEGIN "<!--"
#define rXML_COMMENT_TAG_END "-->"
#define rXML_PROCESS_INSTRUCTION '?'
#define rXML_UNESCAPED_INDICATOR '!'
#define rXML_COMMENT_INDICATOR '-'
#define rXML_CDATA_INDICATOR '['
#define rXML_CDATA_TAG_BEGIN "<![CDATA["
#define rXML_CDATA_TAG_END "]]>"
#define rXML_CATA_TAG "[CDATA["

#define rXML_CARRIAGE_RETURN 0x0D
#define rXML_LINE_FEED 0x0A

//escape strings
#define rXML_LT_STRING "<"
#define rXML_GT_STRING ">"
#define rXML_AMP_STRING "&"
#define rXML_APOS_STRING "'"
#define rXML_QUOTE_STRING "\""
#define rXML_ESCAPE_LT "&lt;"
#define rXML_ESCAPE_GT "&gt;"
#define rXML_ESCAPE_AMP "&amp;"
#define rXML_ESCAPE_APOS "&apos;"
#define rXML_ESCAPE_QUOTE "&quot;"

enum rXMLReaderState{
    rXML_READER_LOOKING_FOR_TAG,
    rXML_READER_STATE_TAG_TYPE,
    rXML_READER_STATE_TAG_NAME,
    rXML_READER_STATE_READING_ELEMENT_VALUE,

    rXML_READER_STATE_TAG_CLOSE,
    rXML_READER_STATE_TAG_END,

    rXML_READER_STATE_LOOKING_FOR_ATTRIBUTES,
    rXML_READER_STATE_ATTRIBUTE_NAME,
    rXML_READER_STATE_ATTRIBUTE_ASSIGN,
    rXML_READER_STATE_ATTRIBUTE_VALUE,

    rXML_READER_STATE_COMMENT_TAG,
    rXML_READER_STATE_READ_COMMENT,

    rXML_READER_STATE_CDATA_TAG,
    rXML_READER_STATE_READING_CDATA_VALUE
};

enum rXMLReaderError{
    rXML_READER_NO_ERROR = 0,
    rXML_READER_FILE_NOT_FOUND,
    rXML_READER_ERROR_TAG_MISMATCH,
    rXML_READER_ERROR_MALFORMED_COMMENT,
    rXML_READER_ERROR_INVALID_MARKUP,
    rXML_READER_ERROR_UNEXPECTED_CHARACTERS,
    rXML_READER_ERROR_INVALID_TAG_NAME,
    rXML_READER_ERROR_CANNOT_READ_STREAM,
    rXML_INVALID_STATE //should never happen.....hopefully
};

class rXMLReader {
public:
    rXMLReader(rXMLReaderDelegate* _delegate = NULL);

	rXMLReaderError ParseFile(const rString& fileName);
	rXMLReaderError ParseStream(rIStream* stream);

    rXMLReaderError Error();
    unsigned int LineNumber();

    bool IsOk();

    void SetDelegate(rXMLReaderDelegate* _delegate);

private:

	void Parse(rIStream* stream);
    void Clear();

private:

    void LookForTag(char c);
	void ParseTagType(char c, rIStream* stream);
    void ParseTagName(char c);
    void ParseElementValue(char c);

    void ParseCloseTag(char c);
    void ParseTagEnd(char c);

    void LookForAttribute(char c);
    void ParseAttributeName(char c);
    void ParseAttributeAssign(char c);
    void ParseAttributeValue(char c);

    void ParseCommentTag(char c);
    void ParseComment(char c);


    void ParseProcessInstructionName(char c);
    void ParseProcessInstruction(char c);

    void ParseCDATATag(char c);
    void ParseCDATAValue(char c);

    void Uncleanse(rString& text);
	char NormalizeNewline(char c, rIStream* stream);

private:
    void SetError(rXMLReaderError e);
    bool CharIsWhitespace(char c);
    bool CharIsQuote(char c);
    void Escape(rString& text, rString ch, rString replacement);

private:
    rXMLAttributeList attributes;
    rString currentToken;

    std::stack<rString> tokenStack;

    unsigned int lineNumber;

private:
    rXMLReaderDelegate* delegate;

    rXMLReaderState state;
    rXMLReaderError error;
};

#endif
