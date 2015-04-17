#include "commands/reSetPropertyCommand.hpp"

reSetPropertyCommand::reSetPropertyCommand(const wxString& actorName, const wxString& propertyName, const wxAny& value, reComponent* component)
	:wxCommand(true, "Set Property")
{
	m_actorName = actorName;
	m_propertyName = propertyName;

	m_newValue = value;

	m_component = component;
	m_firstExecute = true;
}

bool reSetPropertyCommand::Do() {
	if (m_firstExecute){
		m_firstExecute = false;

		if (!GetCurrentPropertyValue())
			return false;
	}

	rActor3* actor = m_component->GetScene()->GetActor(m_actorName.c_str().AsChar());

	if (actor){
		rePropertyWriter writer;
		writer.SetProperty(m_propertyName, m_newValue);
		writer.Write(actor);
		return true;
	}
	
	return false;
}

bool reSetPropertyCommand::Undo() {
	rActor3* actor = m_component->GetScene()->GetActor(m_actorName.c_str().AsChar());

	if (actor){
		rePropertyWriter writer;
		writer.SetProperty(m_propertyName, m_previousValue);
		writer.Write(actor);
		return true;
	}

	return false;
}

bool reSetPropertyCommand::GetCurrentPropertyValue(){
	rActor3* actor = m_component->GetScene()->GetActor(m_actorName.c_str().AsChar());

	rePropertyGetter propertyGetter;

	propertyGetter.GetProperty(m_propertyName, actor);

	if (propertyGetter.PropertySet()){
		m_previousValue = propertyGetter.GetValue();
		return true;
	}
	else {
		return false;
	}
}