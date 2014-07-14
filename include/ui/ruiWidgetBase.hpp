#ifndef RUI_WIDGETBASE_HPP
#define RUI_WIDGETBASE_HPP

#include "rBuild.hpp"

class RECONDITE_API ruiWidgetBase{
public:
	virtual rRect BoundingBox() const = 0;
	virtual rString Id() const = 0;
	virtual rSize Size() const = 0;
	virtual ruiStyle* Style()= 0;
};

#endif