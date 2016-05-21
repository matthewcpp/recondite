#ifndef RUI_LOGTEXT_HPP
#define RUI_LOGTEXT_HPP

#include "ui/ruiWidget.hpp"
#include "rLog.hpp"

class ruiLogText : public ruiWidget, public Log::Target{
public:
	ruiLogText(const rString& id, ruiIDocument* document, rEngine* engine);
	~ruiLogText();

public:
	void SetMaxMessageSize(size_t maxMessageSize);
	size_t MaxMessageSize();

	void Clear();

	virtual void Draw();

	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

public:
	virtual void Debug(const rString& message);
	virtual void Warning(const rString& message);
	virtual void Trace(const rString& message);
	virtual void Info(const rString& message);
	virtual void Error(const rString& message);

private:
	struct Impl;
	Impl* _impl;
};

#endif