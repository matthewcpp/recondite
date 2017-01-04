#ifndef RE_TRANSLATECOMMAND_HPP
#define RE_TRANSLATECOMMAND_HPP

#include "project/reComponent.hpp"

#include <wx/cmdproc.h>

class reTransformCommnad : public wxCommand {
public:
	reTransformCommnad(const wxArrayString& actors, reComponent* component, const wxString& name);

public:
	virtual bool Do() override;
	virtual bool Undo() override;

public:
	void Update(const rVector3& delta);

protected:
	virtual void _ApplyDelta(const rVector3& delta) = 0;

protected:
	wxArrayString _actors;
	rVector3 _transformDelta;

	reComponent* _component;

	bool _firstCommand;
};

class reTranslateCommand : public reTransformCommnad {
public:
	reTranslateCommand(const wxArrayString& actors, reComponent* component);

protected:
	virtual void _ApplyDelta(const rVector3& delta) override;
};

class reRotateCommand : public reTransformCommnad {
public:
	reRotateCommand(const wxArrayString& actors, reComponent* component);

protected:
	void _ApplyDelta(const rVector3& rotationDelta) override;
};

class reScaleCommand : public reTransformCommnad {
public:
	reScaleCommand(const wxArrayString& actors, reComponent* component);

protected:
	virtual void _ApplyDelta(const rVector3& scaleDelta) override;
};

#endif