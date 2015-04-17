#ifndef RE_SETPROPERTYCOMMAND_HPP
#define RE_SETPROPERTYCOMMAND_HPP

#include "project/reComponent.hpp"

#include <wx/wx.h>
#include <wx/cmdproc.h>

#include "ui/rePropertyInterface.hpp"

class reSetPropertyCommand : public wxCommand{
public:
	reSetPropertyCommand(const wxString& actorName, const wxString& propertyName, const wxAny& value, reComponent* component);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

private:
	bool GetCurrentPropertyValue();

private:

	wxString m_actorName;
	wxString m_propertyName;

	wxAny m_newValue;
	wxAny m_previousValue;

	reComponent* m_component;

	bool m_firstExecute;
};

#endif