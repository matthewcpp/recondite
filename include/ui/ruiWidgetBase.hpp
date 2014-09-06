#ifndef RUI_WIDGETBASE_HPP
#define RUI_WIDGETBASE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"
#include "rObject.hpp"

#include "ui/ruiStyle.hpp"

class RECONDITE_API ruiWidgetBase : public rObject{
public:
	ruiWidgetBase(const rString& id, rEngine* engine);

public:
	virtual rRect BoundingBox() const = 0;
	virtual rSize Size() const = 0;

	virtual void Update(rEngine& engine);

public:
	void AddClass(const rString& className);
	void RemoveClass(const rString& className);
	bool HasClass(const rString& className) const;
	void GetClasses(rArrayString& classlist);

	ruiStyle* WidgetStyle();

private:
	int GetClassIndex(const rString& className) const;
	void RecomputeStyle();

private:
	ruiStyle m_style;
	ruiStyle m_computedStyle;
	rArrayString m_classList;
};

#endif