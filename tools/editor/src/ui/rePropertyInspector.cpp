#include "rePropertyInspector.hpp"

rePropertyInspector::rePropertyInspector(reComponent* component, reViewportDisplay* display, wxWindow* parent, wxWindowID id)
	:wxPropertyGrid(parent, id)
{
	m_component = component;
	m_display = display;

	Bind(wxEVT_PG_CHANGED, &rePropertyInspector::OnPropertyValueChanged, this);

	rScene* scene = m_component->GetScene();
	scene->Bind(rEVT_SCENE_LOAD_BEGIN, this, &rePropertyInspector::OnLevelBeginLoad);
	scene->Bind(rEVT_SCENE_ACTOR_RENAMED, this, &rePropertyInspector::OnActorRenamed);

	m_component->Bind(reSELECTION_SELECT, this, &rePropertyInspector::OnSelection);
	m_component->Bind(reSELECTION_SELECT_NONE, this, &rePropertyInspector::OnSelectNone);
}

void rePropertyInspector::OnSelection(rEvent& event){
	reSelectionEvent& selectionEvent = static_cast<reSelectionEvent&>(event);
	Inspect(selectionEvent.Item());
}

void rePropertyInspector::OnSelectNone(rEvent& event){
	Clear();
}

void rePropertyInspector::OnPropertyValueChanged(wxPropertyGridEvent& event){
	
	wxPGProperty* property = event.GetProperty();
	wxStringClientData* propertyInfo = static_cast<wxStringClientData*>(property->GetClientObject());
	wxStringTokenizer tokenizer(propertyInfo->GetData(), ":");
	wxString propertyType = tokenizer.GetNextToken();
	wxString propertyName = tokenizer.GetNextToken();

	rePropertyWriter writer;

	if (propertyType == "vector3"){
		wxVariant x = GetProperty(propertyName + ".x")->GetValue();
		wxVariant y = GetProperty(propertyName + ".y")->GetValue();
		wxVariant z = GetProperty(propertyName + ".z")->GetValue();

		rVector3 vec3(x.GetDouble(), y.GetDouble(), z.GetDouble());

		wxAny any = vec3;
		writer.SetProperty(propertyName, any);
	}
	else if (propertyType == "color"){
		wxAny colorVal = property->GetValue();
		wxColor cpv = colorVal.As<wxColor>();
		rColor c(cpv.Red(), cpv.Green(), cpv.Blue(), cpv.Alpha());

		wxAny any = c;
		writer.SetProperty(propertyName, any);
	}
	else if (propertyType == "int" || propertyType == "float" || propertyType == "string" || propertyType == "bool"){
		wxAny any = property->GetValue();
		writer.SetProperty(propertyName, any);
	}

	if (writer.PropertySet()){
		rActor3* actor = m_component->GetScene()->GetActor(m_actorName.c_str().AsChar());
		writer.Write(actor);
		m_display->UpdateAllViewports();
	}
}

void rePropertyInspector::Inspect(const wxString& actorName){
	rString rstr = actorName.c_str().AsChar();
	rEngine* engine = m_component->GetEngine();

	rActor3* actor = engine->scene->GetActor(rstr);
	
	if (actor){
		m_actorName = actorName;
		rePropertyReader reader(this);
		reader.Read(actor);
	}

}

void rePropertyInspector::StopInspecting(){
	m_actorName = wxEmptyString;
	Clear();
}

void rePropertyInspector::OnLevelBeginLoad(rEvent& event){
	StopInspecting();
}

void rePropertyInspector::OnActorRenamed(rEvent& event){
	rActor3RenameEvent& actorEvent = static_cast<rActor3RenameEvent&> (event);

	wxString oldName = actorEvent.PreviousId().c_str();

	if (oldName == m_actorName){
		wxString newName = actorEvent.Actor()->Id();
		m_actorName = newName;

		wxPGProperty* name = GetProperty("id");
		if (name){
			name->SetValue(newName);
		}
	}
}