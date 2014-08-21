#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rBuild.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "ruiStyle.hpp"

#include "rEngine.hpp"

#include "ui/ruiBase.hpp"
#include "ui/ruiInterface.hpp"
#include "ui/ruiStyleManager.hpp"
#include "ui/ruiStyledWidgetBase.hpp"
#include "ui/ruiGenericWidgetFunctor.hpp"

#include "ui/ruiEventHandler.hpp"


class RECONDITE_API ruiWidget : public ruiStyledWidgetBase, public ruiEventHandler{
public:
	ruiWidget(const rString& id, rEngine* engine);
	ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);

	virtual void Draw(rEngine& engine) = 0;
	virtual void Update(rEngine& engine) {}
	virtual rRect BoundingBox() const;

	virtual rSize Size() const;
	void SetSize(int x, int y);

	virtual rPoint Position() const;
	void SetPosition(int x, int y);
	
	template <typename T>
	void Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method);
	void Trigger(int eventType);

public:
	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);
	virtual void OnTouchUp(const rTouch& touch);

	virtual void OnMouseLeftDown(const rMouseState& mouse);
	virtual void OnMouseLeftUp(const rMouseState& mouse);
	virtual void OnMouseMotion(const rMouseState& mouse);

protected:
	static void ShowModal(ruiWidget* widget);
	static void EndModal(ruiWidget* widget);

protected:
	rSize m_size;
	rPoint m_position;


private:
	void InsertEventBinding(int eventType, ruiWidgetFunctor* functor);
	
private:

	ruiFunctorMap m_eventTable;
};

template <typename T>
void ruiWidget::Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method){
	ruiGenericWidgetFunctor<T>* functor = new ruiGenericWidgetFunctor<T>(target, method);
	InsertEventBinding(eventType, functor);
}

#endif
