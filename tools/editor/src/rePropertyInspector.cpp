#include "rePropertyInspector.hpp"

rePropertyInspector::rePropertyInspector(rwxComponent* component, wxWindow* display, wxWindow* parent, wxWindowID id)
	:wxPropertyGrid(parent, id)
{
	m_component = component;
	m_connector = nullptr;
	m_display = display;

	Bind(wxEVT_PG_CHANGED, &rePropertyInspector::OnPropertyValueChanged, this);
}

void rePropertyInspector::InspectViewport(rViewport* viewport){
	Clear();

	if (m_connector)
		delete m_connector;

	wxPGProperty* name = new wxStringProperty("Name", wxPG_LABEL, viewport->Name().c_str());
	wxPGProperty* classProp = new wxStringProperty("Class", wxPG_LABEL, "Viewport");
	m_connector = new reCameraPropertyConnector((rCamera*)viewport->Camera());

	m_connector->SetPGProperties(this);
	FitColumns();
}

void rePropertyInspector::OnPropertyValueChanged(wxPropertyGridEvent& event){
	wxPGProperty* property = event.GetProperty();
	wxString propertyClass = property->GetValueType();

	bool shouldRefresh = false;

	if (propertyClass == "double")
		shouldRefresh = m_connector->SetDoubleProperty(event.GetPropertyName(), GetPropertyValue(property).GetDouble());
	
	if (propertyClass == "long")
		shouldRefresh = m_connector->SetIntProperty(event.GetPropertyName(), GetPropertyValue(property).GetInteger());
	else if (propertyClass == "wxColour"){
		wxAny colorVal = property->GetValue();
		wxColor cpv = colorVal.As<wxColor>();
		shouldRefresh = m_connector->SetColorProperty(event.GetPropertyName(), cpv);
	}
		
	if (shouldRefresh){
		Freeze();
		m_connector->RefreshPGProperties(this);
		Thaw();

		m_display->Refresh();
	}
}
void rePropertyInspector::Inspect(const wxString& actorName){
	rString rstr = actorName.c_str().AsChar();
	rEngine* engine = m_component->GetEngine();

	rActor3* actor = engine->scene->GetActor(rstr);

	if (m_connector)
		delete m_connector;

	if (actor)
		m_connector = new rPrimitiveBoxPropertyConnector((rPrimitiveBox*)actor);

	m_connector->SetPGProperties(this);
	FitColumns();
}
