#ifndef RE_ACTORPROPERTYCONNECTOR_HPP
#define RE_ACTORPROPERTYCONNECTOR_HPP

#include "rePropertyConnector.hpp"

#include "rActor3.hpp"

class reActorPropertyConnector : public rePropertyConnector{
public:
	reActorPropertyConnector(rActor3* actor);

	virtual void SetPGProperties(wxPropertyGrid* grid);
	virtual void RefreshPGProperties(wxPropertyGrid* grid);

	virtual bool SetDoubleProperty(const wxString& name, double val);

protected:
	virtual void SetClassPGProperties(wxPropertyGrid* grid) = 0;
	virtual void RefreshClassPGProperties(wxPropertyGrid* grid) = 0;

private:
	rActor3* m_actor;
};

#endif