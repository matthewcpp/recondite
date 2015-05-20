#include "rDrawable.hpp"

//-----rDrawable

rDrawable::rDrawable(){
	s_drawableIdManager.GetNextColor(m_pickingColor);

	m_visible = true;
	m_forceRender = false;
	m_shader = nullptr;
}

rDrawable::~rDrawable(){
	s_drawableIdManager.ReturnColor(m_pickingColor);
}

rColor rDrawable::PickingColor() const{
	return m_pickingColor;
}

bool rDrawable::Visible() const{
	return m_visible;
}

void rDrawable::SetVisibility(bool visibility){
	m_visible = visibility;
}

bool rDrawable::ForceRender(){
	return m_forceRender;
}

void rDrawable::SetForceRender(bool forceRender){
	m_forceRender = forceRender;

}

rShader* rDrawable::Shader() const{
	return m_shader;
}

void rDrawable::SetShader(rShader* shader){
	m_shader = shader;
}

PickingColorManager rDrawable::s_drawableIdManager;

//-----rDrawableIdManager

bool PickingColorManager::GetNextColor(rColor& color){
	if (m_availableColors.size() > 0){
		color = m_availableColors.front();
		m_availableColors.pop();
		return true;
	}

	rColor nextColor(r,g,b,a);

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

void PickingColorManager::ReturnColor(const rColor& color){
	m_availableColors.push(color);
}