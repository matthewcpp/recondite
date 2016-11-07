#ifndef RUI_LAYOUT_HPP
#define RUI_LAYOUT_HPP

#include <memory>

#include "rBuild.hpp"

#include "rString.hpp"
#include "rRect.hpp"
#include "rEngine.hpp"
#include "rPoint.hpp"
#include "rPropertyCollection.hpp"

#include "ui/ruiWidget.hpp"

class RECONDITE_API ruiLayout: public ruiWidget {
public:
	ruiLayout(const rString& id, ruiIDocument* document, rEngine* engine);

public:
	virtual void AddItem(ruiWidget* widget);

	virtual void Update();
	virtual void Draw();
	
	size_t ItemCount() const;
	ruiWidget* GetItem(size_t index);
	
	virtual rSize Layout(rRect& rect) = 0;
	virtual void Clear();
	
protected:
	virtual rSize ComputeSize();
	virtual void ChildUpdated(ruiWidget* child);

	typedef std::vector<ruiWidget*> ruiLayoutItemVector;
	
protected:
	ruiLayoutItemVector m_layoutItems;
};

#endif