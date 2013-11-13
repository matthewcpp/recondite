#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "rEngine.hpp"

#include "ui/ruiBase.hpp"
#include "ui/ruiGenericWidgetFunctor.hpp"

class ruiWidget{
public:
	ruiWidget(int id);
	ruiWidget(int id, const rPoint& position, const rSize& size);
	virtual void Draw(rEngine& engine) = 0;
	virtual void Update(rEngine& engine) {}
	virtual rRect BoundingBox() const;
	
	virtual void OnTouchDown(const rTouch& touch) {}
	virtual void OnTouchMove(const rTouch& touch) {}
	virtual void OnTouchUp(const rTouch& touch) {}

	int Id() const;

	rSize Size() const;
	void SetSize(int x, int y);

	rPoint Position() const;
	void SetPosition(int x, int y);
	
	template <typename T>
	void Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method);
	void Trigger(int eventType);

public:
	static ruiIWidgetManager* widgetManager;

protected:
	static void ShowModal(ruiWidget* widget);
	static void EndModal(ruiWidget* widget);

protected:
	rSize m_size;
	rPoint m_position;
	
private:
	int m_id;

	ruiFunctorMap m_eventTable;
};

template <typename T>
void ruiWidget::Bind(int eventType, T* target, typename ruiGenericFunctionPointer<T>::Type method){
	ruiGenericWidgetFunctor<T>* functor = new ruiGenericWidgetFunctor<T>(target, method);
	m_eventTable.insert(std::make_pair(eventType , (ruiWidgetFunctor*)functor));
}

#endif
