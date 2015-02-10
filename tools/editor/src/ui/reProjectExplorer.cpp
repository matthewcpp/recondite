#include "reProjectExplorer.hpp"

reProjectExplorer::reProjectExplorer(rwxComponent* component, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
}