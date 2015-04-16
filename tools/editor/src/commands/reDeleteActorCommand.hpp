#ifndef RE_DELETEACTORCOMMAND_HPP
#define RE_DELETEACTORCOMMAND_HPP

#include "project/reComponent.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLSerialization.hpp"

#include <wx/cmdproc.h>

class reDeleteActorCommand : public wxCommand{
public:
	reDeleteActorCommand(const wxArrayString& actorList, reComponent* component);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

private:
	void SerializeActors();

private:
	wxArrayString m_actorList;
	reComponent* m_component;

	rXMLDocument m_actorData;
};

#endif