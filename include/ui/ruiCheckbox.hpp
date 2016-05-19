#ifndef RUI_CHECKBOX_HPP
#define RUI_CHECKBOX_HPP

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiCheckbox : public ruiWidget{
public:
	ruiCheckbox(const rString& id, ruiIDocument* document, rEngine* engine);
	
public:

	bool IsChecked () const;
	void SetChecked(bool checked);
	
	virtual void Draw();

	rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

protected:

	virtual bool OnPointerUp(const rPoint& position);
	
private:
	bool m_isChecked;
};


#endif
