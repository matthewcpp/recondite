#include "rDrawable.hpp"

//-----rDrawable

rDrawable::rDrawable(){
	s_drawableIdManager.GetNextColor(m_pickingColor);
	m_material = NULL;
	m_visible = true;

	m_renderMode = rRenderMode::Default;
}

rDrawable::~rDrawable(){
	s_drawableIdManager.ReturnColor(m_pickingColor);
}

rColor rDrawable::PickingColor() const{
	return m_pickingColor;
}

rMaterial* rDrawable::Material() const{
	return m_material;
}

void rDrawable::SetMaterial(rMaterial* material){
	m_material = material;
}

bool rDrawable::Visible() const{
	return m_visible;
}

void rDrawable::SetVisibility(bool visibility){
	m_visible = visibility;
}

rPropertyCollection& rDrawable::MaterialProperties(){
	return m_materialProperties;
}

rGeometry* rDrawable::Geometry() const{
	return m_geometry;
}

void rDrawable::SetGeometry(rGeometry* geometry){
	m_geometry = geometry;
}

rRenderMode rDrawable::RenderMode() const{
	return m_renderMode;
}

void rDrawable::SetRenderMode(rRenderMode renderMode){
	m_renderMode = renderMode;
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