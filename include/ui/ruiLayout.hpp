#ifndef RUI_LAYOUT_HPP
#define RUI_LAYOUT_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rRect.hpp"
#include "rEngine.hpp"
#include "rPoint.hpp"
#include "rPropertyCollection.hpp"

#include "ui/ruiWidget.hpp"

class ruiLayoutItem {
public:
	ruiLayoutItem(size_t flags) : m_flags(flags) {}
	virtual ~ruiLayoutItem() {}
	
public:
	virtual void SetPosition(const rPoint& position) = 0;
	virtual rSize GetSize() const = 0;
	virtual const rPropertyCollection* Properties() const = 0;
	
public:
	size_t Flags() {return m_flags;}
	void SetFlags(size_t flags) {m_flags = flags;}
	
private:
	size_t m_flags;
};

class ruiLayout {
public:
	virtual ~ruiLayout();
	
public:
	virtual void AddItem(ruiWidget* widget, size_t flags);
	virtual void AddItem(ruiLayout* layout, size_t flags);

	void SetPosition(const rPoint& position);
	rPoint Position() const;
	
	size_t ItemCount() const;
	
	virtual void Layout(rRect& rect) = 0;
	virtual void Clear();
	virtual rSize Size() const = 0;
	const rPropertyCollection* Properties() const;
	
protected:
	typedef std::vector<ruiLayoutItem*> ruiLayoutItemVector;
	
protected:

	ruiLayoutItemVector m_layoutItems;
	rPoint m_position;

	rPropertyCollection m_properties;
};

class ruiWidgetLayoutItem : public ruiLayoutItem {
public:
	ruiWidgetLayoutItem(ruiWidget* widget, size_t flags);

public:
	virtual void SetPosition(const rPoint& position);
	virtual rSize GetSize() const;
	virtual const rPropertyCollection* Properties() const;

private:
	ruiWidget* m_widget;
};

class ruiLayoutLayoutItem : public ruiLayoutItem {
public:
	ruiLayoutLayoutItem(ruiLayout* layout, size_t flags);

public:
	virtual void SetPosition(const rPoint& position);
	virtual rSize GetSize() const;
	virtual const rPropertyCollection* Properties() const;

private:
	ruiLayout* m_layout;
};

#endif