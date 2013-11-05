#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "rEngine.hpp"

class ruiWidget;

class ruiIWidgetManager{
public:
	virtual void ShowModal(ruiWidget* widget) = 0;
	virtual void EndModal(ruiWidget* widget) = 0;
};

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
	
protected:
	rSize m_size;
	rPoint m_position;
	
private:
	int m_id;
};

#endif
