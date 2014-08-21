#ifndef RUI_WIDGETBASE_HPP
#define RUI_WIDGETBASE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"

class RECONDITE_API ruiWidgetBase{
public:
	ruiWidgetBase(const rString& id, rEngine* engine) : m_id(id), m_engine(engine) {}

public:

	rString Id() const { return m_id; }

public:
	virtual rRect BoundingBox() const = 0;
	virtual rSize Size() const = 0;

protected:

	rEngine* m_engine;

private:
	rString m_id;
};

#endif