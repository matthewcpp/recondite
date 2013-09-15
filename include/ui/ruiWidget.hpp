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
	ruiWidget(int id, const rPoint& position, const rSize& size);
	virtual void Draw(rRenderer* renderer) = 0;
	virtual void Update(rEngine& engine) = 0;
	
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