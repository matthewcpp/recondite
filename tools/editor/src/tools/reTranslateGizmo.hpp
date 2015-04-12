#ifndef RE_TRANSLATEGIZMO_HPP
#define RE_TRANSLATEGIZMO_HPP

#include "project/reComponent.hpp"
#include "rProp.hpp"

class reTranslateGizmo{
public:
	reTranslateGizmo(reComponent* component);

public:
	void SetVisibility(bool visibility);
	void SetPosition(const rVector3& position);
	void Update();

	bool ContainsActor(rActor3* actor);

private:
	void CreateGizmo();

private:
	reComponent* m_component;
	rProp* m_prop;
};

#endif