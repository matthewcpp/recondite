#include "reOutliner.hpp"

reOutliner::reOutliner(rwxComponent* component, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
}