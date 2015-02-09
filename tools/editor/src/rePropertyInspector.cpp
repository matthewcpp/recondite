#include "rePropertyInspector.hpp"

rePropertyInspector::rePropertyInspector(rwxComponent* component, wxWindow* parent, wxWindowID id)
	:wxPropertyGrid(parent, id)
{
	m_component = component;
}