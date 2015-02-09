#include "reActorPropertyConnector.hpp"

reActorPropertyConnector::reActorPropertyConnector(rActor3* actor){
	m_actor = actor;
}

void reActorPropertyConnector::SetPGProperties(wxPropertyGrid* grid){
	rString className = m_actor->ClassName();
	wxPGProperty* name = new wxStringProperty("Name", wxPG_LABEL, m_actor->Id().c_str());
	wxPGProperty* classProp = new wxStringProperty("Class", wxPG_LABEL, className.c_str());
	grid->Append(name);
	grid->Append(classProp);
	grid->EnableProperty(name, false);
	grid->EnableProperty(classProp, false);

	SetClassPGProperties(grid);

	grid->Append(new wxPropertyCategory("Actor", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Position X", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Position Y", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Position Z", wxPG_LABEL));

	grid->Append(new wxFloatProperty("Rotation X", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Rotation Y", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Rotation Z", wxPG_LABEL));

	grid->Append(new wxFloatProperty("Scale X", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Scale Y", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Scale Z", wxPG_LABEL));

	RefreshPGProperties(grid);
}

void reActorPropertyConnector::RefreshPGProperties(wxPropertyGrid* grid){
	rVector3 position = m_actor->Position();
	rVector3 rotation = m_actor->Rotation();
	rVector3 scale = m_actor->Scale();

	grid->SetPropertyValue("Position X", position.x);
	grid->SetPropertyValue("Position Y", position.y);
	grid->SetPropertyValue("Position Z", position.z);

	grid->SetPropertyValue("Rotation X", rotation.x);
	grid->SetPropertyValue("Rotation Y", rotation.y);
	grid->SetPropertyValue("Rotation Z", rotation.z);

	grid->SetPropertyValue("Scale X", scale.x);
	grid->SetPropertyValue("Scale Y", scale.y);
	grid->SetPropertyValue("Scale Z", scale.z);

	RefreshClassPGProperties(grid);
}

bool reActorPropertyConnector::SetDoubleProperty(const wxString& name, double val){
	bool refresh = false;
	
	if (name == "Position X"){
		rVector3 pos = m_actor->Position();
		pos.x = val;
		m_actor->SetPosition(pos);
		refresh = true;
	}
	else if (name == "Position Y"){
		rVector3 pos = m_actor->Position();
		pos.y = val;
		m_actor->SetPosition(pos);
		refresh = true;
	}
	else if (name == "Position Z"){
		rVector3 pos = m_actor->Position();
		pos.z = val;
		m_actor->SetPosition(pos);
		refresh = true;
	}

	else if (name == "Rotation X"){
		rVector3 rot = m_actor->Rotation();
		rot.x = val;
		m_actor->SetRotation(rot);
		refresh = true;
	}
	else if (name == "Rotation Y"){
		rVector3 rot = m_actor->Rotation();
		rot.y = val;
		m_actor->SetRotation(rot);
		refresh = true;
	}
	else if (name == "Rotation Z"){
		rVector3 rot = m_actor->Rotation();
		rot.z = val;
		m_actor->SetRotation(rot);
		refresh = true;
	}

	else if (name == "Scale X"){
		rVector3 scale = m_actor->Scale();
		scale.x = val;
		m_actor->SetScale(scale);
		refresh = true;
	}
	else if (name == "Scale Y"){
		rVector3 scale = m_actor->Scale();
		scale.y = val;
		m_actor->SetScale(scale);
		refresh = true;
	}
	else if (name == "Scale Z"){
		rVector3 scale = m_actor->Scale();
		scale.z = val;
		m_actor->SetScale(scale);
		refresh = true;
	}

	return refresh;
}