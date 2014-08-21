#ifndef RUI_STYLEDWIDGETBASE_HPP
#define RUI_STYLEDWIDGETBASE_HPP

#include "rBuild.hpp"
#include "ui/ruiStyle.hpp"

#include "ui/ruiWidgetBase.hpp"

class RECONDITE_API ruiStyledWidgetBase : public ruiWidgetBase{
public:
	ruiStyledWidgetBase(const rString& id, rEngine* engine);

	void RecomputeStyle();

public:
	void AddClass(const rString& className);
	void RemoveClass(const rString& className);
	bool HasClass(const rString& className) const;
	void GetClasses(rArrayString& classlist);

	ruiStyle* WidgetStyle();

private:
	int GetClassIndex(const rString& className) const;

private:
	ruiStyle m_style;
	ruiStyle m_computedStyle;
	rArrayString m_classList;
};

#endif