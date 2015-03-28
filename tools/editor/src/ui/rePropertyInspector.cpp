#include "rePropertyInspector.hpp"

rePropertyInspector::rePropertyInspector(reComponent* component, reViewportDisplay* display, wxWindow* parent, wxWindowID id)
	:wxPropertyGrid(parent, id)
{
	m_component = component;
	m_connector = nullptr;
	m_display = display;

	Bind(wxEVT_PG_CHANGED, &rePropertyInspector::OnPropertyValueChanged, this);

	rScene* scene = m_component->GetScene();
	scene->Bind(rEVT_SCENE_LOAD_BEGIN, this, &rePropertyInspector::OnLevelBeginLoad);
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

		m_display->UpdateDisplay();
	}
}

rePropertyConnector* rePropertyInspector::GetConnector(rActor3* actor){
	if (!actor) return nullptr;

	rePropertyConnector* connector = nullptr;

	rString className = actor->ClassName();

	if (className == "PrimitiveBox")
		connector = new rPrimitiveBoxPropertyConnector((rPrimitiveBox*)actor);
	else if (className == "PrimitiveGrid")
		connector = new rPrimitiveGridPropertyConnector((rPrimitiveGrid*)actor);

	return connector;
}

void rePropertyInspector::Inspect(const wxString& actorName){
	rString rstr = actorName.c_str().AsChar();
	rEngine* engine = m_component->GetEngine();

	rActor3* actor = engine->scene->GetActor(rstr);
	rePropertyConnector* newConnector = GetConnector(actor);

	wxString oldClass, newClass;

	if (m_connector){
		oldClass = m_connector->GetConnectionClass();
		delete m_connector;
	}

	if (newConnector){
		m_connector = newConnector;
		newClass = newConnector->GetConnectionClass();

		if (newClass == oldClass){
			m_connector->RefreshPGProperties(this);
		}
		else{
			Clear();
			m_connector->SetPGProperties(this);
			FitColumns();
		}
	}
	else{ //unable to find a connector for this actor.
		m_connector = nullptr;
		Clear();
	}
}

void rePropertyInspector::StopInspecting(){
	if (m_connector){
		delete m_connector;
		m_connector = nullptr;
	}

	Clear();
}

void rePropertyInspector::OnLevelBeginLoad(rEvent& event){
	Clear();
}