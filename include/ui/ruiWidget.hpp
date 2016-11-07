#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"
#include "rObject.hpp"
#include "ruiStyle.hpp"

#include "ruiDefaultEventHandler.hpp"
#include "rPropertyCollection.hpp"

class ruiIDocument;

class RECONDITE_API ruiWidget : public rObject, public ruiDefaultEventHandler{
public:
	ruiWidget(const rString& id, ruiIDocument* document, rEngine* engine);

public:
	virtual rRect BoundingBox();
	virtual rSize Size();
	virtual rPoint Position() const;

	virtual void Update();
	virtual void Draw();

	virtual void SetPosition(const rPoint& position);

public:
	virtual void AddClass(const rString& className);
	virtual void RemoveClass(const rString& className);
	bool HasClass(const rString& className) const;
	void GetClasses(rArrayString& classlist);

	ruiStyle* Style();
	ruiStyle* ComputedStyle();

	virtual rString GetWidgetType() const = 0;

	rString UiState() const;
	void UiState(const rString& state);

	rPropertyCollection& Properties();

	void RecomputeSize(bool force = false);

protected: //style related utility methods
	Font::Face* DetermineFont();

protected:
	virtual rSize ComputeSize() = 0;
	void InvalidateSize();
	
	rPoint ContentOffset();
	void RenderWidgetBase(ruiStyle* style, const rRect& boundingBox);

private:
	int GetClassIndex(const rString& className) const;
	void RecomputeContentOffset();
	void RecomputeStyle();
	void ExtendStyle(const rString& selector);
	

protected:
	ruiIDocument* m_document;

	rPoint ContentPosition();
	rPoint m_position;

private:
	ruiStyle m_style;
	ruiStyle m_computedStyle;
	rArrayString m_classList;
	rString m_uiState;

	rSize m_size;
	rPoint m_contentOffset;
	rPropertyCollection m_properties;
};

#endif
