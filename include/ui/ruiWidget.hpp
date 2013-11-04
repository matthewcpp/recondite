#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "rEngine.hpp"

class ruiWidget{
public:
	ruiWidget(int id);
	ruiWidget(int id, const rPoint& position, const rSize& size);
	virtual void Draw(rEngine& engine) = 0;
	virtual void Update(rEngine& engine) = 0;
	virtual rRect BoundingBox() const;
	
	virtual void OnTouchDown(const rTouch& touch) {}
	virtual void OnTouchMove(const rTouch& touch) {}
	virtual void OnTouchUp(const rTouch& touch) {}

	int Id() const;
	rSize Size() const;
	rPoint Position() const;
	
protected:
	rSize m_size;
	rPoint m_position;
	
private:
	int m_id;
};

#endif
