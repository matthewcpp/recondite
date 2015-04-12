#ifndef RE_TRANSLATECOMMAND_HPP
#define RE_TRANSLATECOMMAND_HPP

#include "project/reComponent.hpp"

#include <wx/cmdproc.h>

class reTranslateCommand : public wxCommand{
public:
	reTranslateCommand(const wxArrayString& actors, reComponent* component);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

public:
	void Update(const rVector3& delta);

private:
	void AddActorPositions(const rVector3& delta);

private:
	wxArrayString m_actors;
	rVector3 translateVector;

	reComponent* m_component;

	bool m_firstCommand;
};

#endif