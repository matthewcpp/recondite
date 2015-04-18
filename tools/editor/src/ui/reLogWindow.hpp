#ifndef RE_LOGWINDOW_HPP
#define RE_LOGWINDOW_HPP

#include "project/reComponent.hpp"

#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/listctrl.h>

#include "rLog.hpp"

class reLogWindow : public wxPanel , public rLogTarget{
public:
	reLogWindow(reComponent* component, wxWindow* parent, wxWindowID id = wxID_ANY);

public:

	virtual void Debug(const rString& message) override;
	virtual void Warning(const rString& message) override;
	virtual void Trace(const rString& message) override;
	virtual void Info(const rString& message) override;
	virtual void Error(const rString& message) override;

	virtual void Shutdown() override;

private:
	enum class LogTypeIndex{ Debug, Warning, Trace, Info, Error };

	void InitControls();

	void AddItem(LogTypeIndex logType, const rString& message);

private:
	reComponent* m_component;

	wxListView* m_logList;
	
};

#endif