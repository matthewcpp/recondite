#include "reCameraPropertyConnector.hpp"

reCameraPropertyConnector::reCameraPropertyConnector(rCamera* camera)
	:reActorPropertyConnector(camera)
{
	m_camera = camera;
}

void reCameraPropertyConnector::SetClassPGProperties(wxPropertyGrid* grid){
	rString className = m_camera->ClassName();

	grid->Append(new wxPropertyCategory(className.c_str(), wxPG_LABEL));
	grid->Append(new wxFloatProperty("Target X", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Target Y", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Target Z", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Up X", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Up Y", wxPG_LABEL));
	grid->Append(new wxFloatProperty("Up Z", wxPG_LABEL));
}

void reCameraPropertyConnector::RefreshClassPGProperties(wxPropertyGrid* grid){
	rVector3 target = m_camera->Target();
	rVector3 up = m_camera->Up();

	grid->SetPropertyValue("Target X", target.x);
	grid->SetPropertyValue("Target Y", target.y);
	grid->SetPropertyValue("Target Z", target.z);

	grid->SetPropertyValue("Up X", up.x);
	grid->SetPropertyValue("Up Y", up.y);
	grid->SetPropertyValue("Up Z", up.z);

}

