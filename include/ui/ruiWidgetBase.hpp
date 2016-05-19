#ifndef RUI_WIDGETBASE_HPP
#define RUI_WIDGETBASE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"
#include "rObject.hpp"
#include "ruiStyle.hpp"

class ruiDocument;

class RECONDITE_API ruiWidgetBase : public rObject{
public:
	ruiWidgetBase(const rString& id, ruiDocument* document, rEngine* engine);

public:
	virtual rRect BoundingBox() = 0;
	virtual rSize Size();
	virtual rPoint Position() const = 0;

	virtual void Update();
	virtual void Draw();

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

protected: //style related utility methods
	Font::Face* DetermineFont();

protected:
	virtual rSize ComputeSize() = 0;
	void InvalidateSize();
	rPoint ContentOffset();
	void RenderWidgetBase(ruiStyle* style, const rRect& boundingBox);

private:
	int GetClassIndex(const rString& className) const;
	void RecomputeStyle();
	void ExtendStyle(const rString& selector);
	void RecomputeSize(bool force = false);

protected:
	ruiDocument* m_document;
	
private:
	ruiStyle m_style;
	ruiStyle m_computedStyle;
	rArrayString m_classList;
	rString m_uiState;

	rSize m_size;
	rPoint m_contentOffset;
};

#endif