#include "rRenderingOptions.hpp"

rPickingColorManager rRenderingOptions::s_pickingColorManager;

bool rPickingColorManager::GetNextColor(rColor& color){
	if (m_availableColors.size() > 0){
		color = m_availableColors.front();
		m_availableColors.pop();
		return true;
	}

	rColor nextColor(r, g, b, a);

	if (r < UINT8_MAX)
		r++;
	else if (g < UINT8_MAX)
		g++;
	else if (b < UINT8_MAX)
		b++;
	else
		return false;

	color = nextColor;
	return true;
}

void rPickingColorManager::ReturnColor(const rColor& color){
	m_availableColors.push(color);
}

rRenderingOptions::rRenderingOptions(){
	m_visibility = true;
	m_forceRender = false;
	s_pickingColorManager.GetNextColor(m_pickingColor);
}

rRenderingOptions::~rRenderingOptions(){
	s_pickingColorManager.ReturnColor(m_pickingColor);
}

bool rRenderingOptions::ForceRender() const{
	return m_forceRender;
}

void rRenderingOptions::SetForceRender(bool forceRender){
	m_forceRender = forceRender;
}

bool rRenderingOptions::Visible() const{
	return m_visibility;
}

void rRenderingOptions::SetVisibility(bool visible){
	m_visibility = visible;
}

bool rRenderingOptions::Overdraw() const{
	return m_overdraw;
}

void rRenderingOptions::SetOverdraw(bool overdraw){
	m_overdraw = overdraw;
}

rColor rRenderingOptions::PickingColor() const{
	return m_pickingColor;
}