#ifndef RE_INSERTACTORCOMMAND_HPP
#define RE_INSERTACTORCOMMAND_HPP

#include "project/reComponent.hpp"
#include "rVector3.hpp"

#include <wx/cmdproc.h>

class reInsertActorCommand : public wxCommand{
public:
	reInsertActorCommand(const wxString& actorCreateStr, const rVector3& position, reComponent* component);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

private:
	wxString m_actorCreateStr;
	rString m_actorId;

	rVector3 m_position;

	reComponent* m_component;
};

#endif