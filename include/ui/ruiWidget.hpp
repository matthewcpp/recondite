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
#include "ui/ruiWidgetBase.hpp"
#include "ui/ruiGenericWidgetFunctor.hpp"

#include "ui/ruiEventHandler.hpp"

class RECONDITE_API ruiWidget : public ruiWidgetBase, public ruiEventHandler{
public:
	ruiWidget(const rString& id, ruiIOverlay* overlay, rEngine* engine);
	ruiWidget(const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size);

	virtual void Draw(rEngine& engine) = 0;
	virtual void Update(rEngine& engine) {}
	virtual rRect BoundingBox() const;

	virtual rString Id() const;

	virtual rSize Size() const;
	void SetSize(int x, int y);

	virtual rPoint Position() const;
	void SetPosition(int x, int y);
	
	template <typename T>
	void Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method);
	void Trigger(int eventType);

	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);
	virtual void OnTouchUp(const rTouch& touch);

	virtual void OnMouseLeftDown(const rMouseState& mouse);
	virtual void OnMouseLeftUp(const rMouseState& mouse);
	virtual void OnMouseMotion(const rMouseState& mouse);

	virtual ruiStyle* Style();

public:
	static ruiIOverlay* widgetManager;

protected:
	static void ShowModal(ruiWidget* widget);
	static void EndModal(ruiWidget* widget);

protected:
	rSize m_size;
	rPoint m_position;

	ruiStyle m_style;
	ruiStyle m_computedStyle;

	rEngine* m_engine;
	ruiIOverlay* m_overlay;

private:
	void InsertEventBinding(int eventType, ruiWidgetFunctor* functor);
	
private:
	rString m_id;

	ruiFunctorMap m_eventTable;
};

template <typename T>
void ruiWidget::Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method){
	ruiGenericWidgetFunctor<T>* functor = new ruiGenericWidgetFunctor<T>(target, method);
	InsertEventBinding(eventType, functor);
}

#endif
