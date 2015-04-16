#ifndef RE_ACTORCOMMANDS_HPP
#define RE_ACTORCOMMANDS_HPP

#include "project/reComponent.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLSerialization.hpp"

#include <wx/cmdproc.h>

//Insert
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


//Delete

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

//Rename
class reRenameActorCommand : public wxCommand{
public:
	reRenameActorCommand(const wxString& oldName, const wxString& newName, reComponent* component);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

private:
	wxString m_oldName;
	wxString m_newName;

	reComponent* m_component;
};

#endif