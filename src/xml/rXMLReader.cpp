#include "xml/rXMLReader.hpp"

rXMLReader::rXMLReader(rXMLReaderDelegate* _delegate)
{
    delegate = _delegate;
    Clear();
}

void rXMLReader::Parse(std::istream* stream){

    if (delegate)
        delegate->OnBeginParseDocument();

    char character;

    while (stream->good() && stream->peek()!=EOF){
        character = stream->get();

        if (character == rXML_CARRIAGE_RETURN)
            character = NormalizeNewline(character, stream);

        if (character == rXML_LINE_FEED){
            lineNumber++;
            continue;
        }

        switch (state){
            case rXML_READER_LOOKING_FOR_TAG:
                LookForTag(character);
                break;

            case rXML_READER_STATE_TAG_TYPE:
                ParseTagType(character, stream);
                break;


            case rXML_READER_STATE_TAG_NAME:
                ParseTagName(character);
                break;



            case rXML_READER_STATE_READING_ELEMENT_VALUE:
                ParseElementValue(character);
                break;

            case rXML_READER_STATE_TAG_END:
                ParseTagEnd(character);
                break;


            case rXML_READER_STATE_LOOKING_FOR_ATTRIBUTES:
                LookForAttribute(character);
                break;

            case rXML_READER_STATE_ATTRIBUTE_NAME:
                ParseAttributeName(character);
                break;

            case rXML_READER_STATE_ATTRIBUTE_ASSIGN:
                ParseAttributeAssign(character);
                break;
                
            case rXML_READER_STATE_ATTRIBUTE_VALUE:
                ParseAttributeValue(character);
                break;

            case rXML_READER_STATE_TAG_CLOSE:
                ParseCloseTag(character);
                break;


            case rXML_READER_STATE_COMMENT_TAG:
                ParseCommentTag(character);
                break;

            case rXML_READER_STATE_READ_COMMENT:
                ParseComment(character);
                break;

            case rXML_READER_STATE_CDATA_TAG:
                ParseCDATATag(character);
                break;

            case rXML_READER_STATE_READING_CDATA_VALUE:
                ParseCDATAValue(character);
                break;

            default:
                SetError(rXML_INVALID_STATE);
        };

        if (error)
            break;
    }


    if (delegate)
        delegate->OnEndParseDocument();

}

bool rXMLReader::IsOk(){
    return error == rXML_READER_NO_ERROR;
}

void rXMLReader::LookForTag(char c){
    if (c == rXML_TAG_BEGIN){
        state = rXML_READER_STATE_TAG_TYPE;
    }
    else if (!CharIsWhitespace(c)){
        SetError(rXML_READER_ERROR_UNEXPECTED_CHARACTERS);
    }
}

//fires when we start reading a tag <
void rXMLReader::ParseTagType(char c,std::istream* stream){
    if (c == rXML_UNESCAPED_INDICATOR){

        //! indicates either a comment or CDATA..need to know which
        if (stream->peek() == rXML_COMMENT_INDICATOR)
            state = rXML_READER_STATE_COMMENT_TAG;
        else if (stream->peek() == rXML_CDATA_INDICATOR)
            state = rXML_READER_STATE_CDATA_TAG;
        else{ //invalid character here...error out
            SetError(rXML_READER_ERROR_INVALID_MARKUP);
            return;
        }

        currentToken.clear();
    }
    else if (c == rXML_TAG_CLOSE){
        state = rXML_READER_STATE_TAG_END;
        currentToken.clear();
    }

    else if (c == rXML_PROCESS_INSTRUCTION){
        state = rXML_READER_STATE_TAG_NAME;
        currentToken.clear();
    }

    //reading element tag
    else if (!CharIsWhitespace(c)){
        state = rXML_READER_STATE_TAG_NAME;
        currentToken = std::string(1, c);
    }
}

void rXMLReader::ParseTagName(char c){
    //did we finish reading the name?
    if (CharIsWhitespace(c)){
        state = rXML_READER_STATE_LOOKING_FOR_ATTRIBUTES;
        tokenStack.push(currentToken);
    }
    else if (c == rXML_TAG_END){//no attributes here

        if (delegate)
            delegate->OnStartElement(currentToken, attributes);
        
        state = rXML_READER_STATE_READING_ELEMENT_VALUE;

        tokenStack.push(currentToken);
        currentToken.clear();
    }
    else{//continue reading tag name
        currentToken += c; //in future if we get an invalid char then need to trow an error
    }
}

void rXMLReader::ParseElementValue(char c){
    //found a new tag..send current token and figure out what it is
    if (c == rXML_TAG_BEGIN){

        if (!currentToken.empty()){
            if (delegate)
                delegate->OnReadCharacters(currentToken);
            
            currentToken.clear();
        }

        state = rXML_READER_STATE_TAG_TYPE;
    }
    //if we find some whitespace and have read a token then send to delegate and clear
    else if (CharIsWhitespace(c)){
        if (!currentToken.empty()){
            if (delegate){
                Uncleanse(currentToken);
                delegate->OnReadCharacters(currentToken);
            }
            
            currentToken.clear();
        }
    }
    //continue building element value
    else currentToken += c;
}

void rXMLReader::ParseTagEnd(char c){
    //read the end of the tag, compare to make sure they match
    if (c == rXML_TAG_END){
        if (currentToken == tokenStack.top()){

            if (delegate)
                delegate->OnEndElement(tokenStack.top());

            tokenStack.pop();
            currentToken.clear();

            if (tokenStack.empty())
                state = rXML_READER_LOOKING_FOR_TAG;
            else
                state = rXML_READER_STATE_READING_ELEMENT_VALUE;

        }
        else{
            SetError(rXML_READER_ERROR_TAG_MISMATCH);
            
            return;
        }
    }
    else
        currentToken += c;
}

void rXMLReader::ParseCommentTag(char c){
    if (c != rXML_COMMENT_INDICATOR){
        SetError(rXML_READER_ERROR_INVALID_TAG_NAME);
        return;
    }

    currentToken += c;

    //check to see if the comment has ended....
    if (currentToken == std::string(2, rXML_COMMENT_INDICATOR)){
        currentToken.clear();
        state = rXML_READER_STATE_READ_COMMENT;
    }
}

void rXMLReader::ParseComment(char c){
    currentToken += c;
    

    //check to see if the comment has ended
    if (c == rXML_TAG_END && currentToken.length() > 3){
        int pos = currentToken.length() - 3;
        if (currentToken.substr(pos, 3) == rXML_COMMENT_TAG_END){
            if (delegate)
                delegate->OnComment(currentToken.substr(0, currentToken.length() -3));

            currentToken .clear();

            if (tokenStack.empty())
                state = rXML_READER_LOOKING_FOR_TAG;
            else
                state = rXML_READER_STATE_READING_ELEMENT_VALUE;
        }
    }
}

void rXMLReader::ParseProcessInstruction(char c){

}



void rXMLReader::LookForAttribute(char c){

    //read the last attribute?..need dispatch begin tag event
    if (c == rXML_TAG_END){
        if (delegate)
            delegate->OnStartElement(tokenStack.top(), attributes);
        
        currentToken.clear();
        attributes.Clear();
        state = rXML_READER_STATE_READING_ELEMENT_VALUE;
    }
    else if (c == rXML_TAG_CLOSE){
        // no value contained in this element
        state = rXML_READER_STATE_TAG_CLOSE;
    }
    else if (!CharIsWhitespace(c)){
        currentToken = std::string(1,c);
        state = rXML_READER_STATE_ATTRIBUTE_NAME;
    }
    //need to ensure that the character is not an escapable character or quote..if so throw error?
    
}

void rXMLReader::ParseAttributeName(char c){
    // if i found an equals or whitespace then i have read the entire name
    if (c == rXML_EQUALS || CharIsWhitespace(c)){
        state = rXML_READER_STATE_ATTRIBUTE_ASSIGN;
        tokenStack.push(currentToken);
        currentToken.clear();

        if (c == rXML_EQUALS){
            tokenStack.push(std::string(1 , rXML_EQUALS));
        }
    }
    else{
        currentToken += c;
        //need to check for invalid chars here i.e '<' , ' ' and throw error
    }

    //need to add check for invalid characters
}

void rXMLReader::ParseAttributeAssign(char c){
    // loooking for a =
    if (tokenStack.top() != std::string(1 , rXML_EQUALS)){

        if (c == rXML_EQUALS){
            tokenStack.push(std::string(1 , rXML_EQUALS));
        }

        //if we find a non whitespace then there is an error
        else if (!CharIsWhitespace(c)){
            SetError(rXML_READER_ERROR_UNEXPECTED_CHARACTERS);
            return;
        }

    }
    else{ //found equal sign...looking for a quote
        if (CharIsQuote(c)){
            tokenStack.pop();
            tokenStack.push(std::string(1 , c));
            state = rXML_READER_STATE_ATTRIBUTE_VALUE;
            currentToken.clear();
        }
        else if (!CharIsWhitespace(c)){ //found out of place character
            SetError(rXML_READER_ERROR_UNEXPECTED_CHARACTERS);
            return;
        }
        
        //otherwise eat whitespace
    }
}

void rXMLReader::ParseAttributeValue(char c){
    if (CharIsQuote(c)){//time to end reading attribute value?
        //if the quotes match up then we have read an attribute..need to add it to the attribute list
        if (tokenStack.top() == std::string(1 , c)){
            tokenStack.pop();
            Uncleanse(currentToken);
            attributes.SetAttribute<rString>(tokenStack.top(), currentToken);
            tokenStack.pop();
            currentToken.clear();
            state = rXML_READER_STATE_LOOKING_FOR_ATTRIBUTES;
        }
    }

    //otherwise append to value
    currentToken += c;

    //need to check for problem characters also...
}




void rXMLReader::ParseCloseTag(char c){
    if (c == rXML_TAG_END){
        //end the tag, notify delegate, and cleanup anything involving this tag..
        if (delegate){
            delegate->OnStartElement(tokenStack.top(), attributes);
            delegate->OnEndElement(tokenStack.top());
        }

        tokenStack.pop();
        attributes.Clear();
        currentToken.clear();

        if (tokenStack.empty())
            state = rXML_READER_LOOKING_FOR_TAG;
        else
            state = rXML_READER_STATE_READING_ELEMENT_VALUE;
    }
    else if (!CharIsWhitespace(c)){//some sort of syntax error
        SetError(rXML_READER_ERROR_INVALID_MARKUP);
        return;
    }
}

void rXMLReader::ParseCDATATag(char c){
    currentToken += c;
    
    //have read enough characters to form CDATA tag
    if (currentToken.length() == 7){
        
        if (currentToken == rXML_CATA_TAG)
            state = rXML_READER_STATE_READING_CDATA_VALUE;
        else{
            SetError(rXML_READER_ERROR_INVALID_TAG_NAME);
            return;
        }

        currentToken.clear();
    }
}

void rXMLReader::ParseCDATAValue(char c){
    currentToken += c;


    //check to see if the CDATA sequence has happened
    if (c == rXML_TAG_END && currentToken.length() > 3){
        int pos = currentToken.length() - 3;
        if (currentToken.substr(pos, 3) == rXML_CDATA_TAG_END){
            if (delegate)
                delegate->OnReadCDATA(currentToken.substr(0, currentToken.length() -3));

            currentToken.clear();
            if (tokenStack.empty())
                state = rXML_READER_LOOKING_FOR_TAG;
            else
                state = rXML_READER_STATE_READING_ELEMENT_VALUE;
        }
    }
}

void rXMLReader::Uncleanse(std::string& text){
    Escape(text, rXML_ESCAPE_LT , rXML_LT_STRING);
    Escape(text, rXML_ESCAPE_GT , rXML_GT_STRING);
    Escape(text, rXML_ESCAPE_APOS , rXML_APOS_STRING);
    Escape(text, rXML_ESCAPE_QUOTE , rXML_QUOTE_STRING);
    Escape(text, rXML_ESCAPE_AMP , rXML_AMP_STRING);
}

bool rXMLReader::CharIsWhitespace(char c){
    return c <= rXML_SPACE;
}

bool rXMLReader::CharIsQuote(char c){
    return (c == rXML_QUOTE || c == rXML_APOS);
}

char rXMLReader::NormalizeNewline(char c,std::istream* stream){
    //handle windoez CR + LF
    if (stream->peek() == rXML_LINE_FEED)
        return stream->get();
    else //handle case where only carriage return is used
        return rXML_LINE_FEED;
}

rXMLReaderError rXMLReader::Error(){
    return error;
}

unsigned int rXMLReader::LineNumber(){
    return lineNumber;
}

void rXMLReader::SetError(rXMLReaderError e){
    error = e;
    if (delegate)
        delegate->OnParseError(error, lineNumber);
}

void rXMLReader::SetDelegate(rXMLReaderDelegate* _delegate){
    delegate = _delegate;
}

rXMLReaderError rXMLReader::ParseStream(std::istream* stream){
    Clear();
    Parse(stream);
    return error;
}

rXMLReaderError rXMLReader::ParseFile(std::string fileName){
    Clear();
    std::ifstream stream(fileName.c_str() , std::ios::binary);

    if (!stream.good())
        error = rXML_READER_FILE_NOT_FOUND;

    if (!error)
        Parse(&stream);

    stream.close();

    return error;
}

void rXMLReader::Clear(){
    error = rXML_READER_NO_ERROR;
    lineNumber = 1;
    state = rXML_READER_LOOKING_FOR_TAG;

    currentToken.clear();
    attributes.Clear();

    while (tokenStack.size() > 0)
        tokenStack.pop();
}

void rXMLReader::Escape(std::string& text, std::string ch, std::string replacement){
    size_t searchPos = 0;
    size_t matchPos = text.find(ch, searchPos);

    while (matchPos != std::string::npos){
        text = text.replace(matchPos ,ch.length() ,replacement);
        searchPos = matchPos +1;
        matchPos = text.find(ch, searchPos);
    }
}
