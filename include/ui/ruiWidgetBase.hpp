#ifndef RUI_WIDGETBASE_HPP
#define RUI_WIDGETBASE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"
#include "rObject.hpp"

class RECONDITE_API ruiWidgetBase : public rObject{
public:
	ruiWidgetBase(const rString& id, rEngine* engine) :rObject(id, engine) {}

public:
	virtual rRect BoundingBox() const = 0;
	virtual rSize Size() const = 0;
};

#endif