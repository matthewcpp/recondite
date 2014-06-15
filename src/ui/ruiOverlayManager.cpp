#include "ui/ruiOverlayManager.hpp"

ruiOverlayManager::ruiOverlayManager(){

}

ruiOverlayManager::~ruiOverlayManager(){
	Clear();
}

ruiOverlay* ruiOverlayManager::CreateOverlay(rViewport* viewport){
	ruiViewportOverlayMap::iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end()){
		delete result->second;
	}

	ruiOverlay* overlay = new ruiOverlay();
	m_overlays[viewport] = overlay;

	return overlay;
}

void ruiOverlayManager::Clear(){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		delete it->second;
	}

	m_overlays.clear();
}

rViewport* ruiOverlayManager::DetermineViewport(const rPoint& point){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		rRect screenRect = it->first->GetScreenRect();

		if (screenRect.ContainsPoint(point))
			return it->first;
	}

	return NULL;
}



void ruiOverlayManager::Update(rEngine& engine){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		it->second->Update(engine);
	}
}

void ruiOverlayManager::Draw(rViewport* viewport, rEngine& engine){
	ruiViewportOverlayMap::iterator vp = m_overlays.find(viewport);

	if (vp != m_overlays.end())
		vp->second->Draw(engine);
}

bool ruiOverlayManager::InjectKeyDownEvent(rKey key, rKeyboardState& state){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		it->second->InjectKeyDownEvent(key, state);
	}

	return false;
}

bool ruiOverlayManager::InjectKeyUpEvent(rKey key, rKeyboardState& state){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		it->second->InjectKeyUpEvent(key, state);
	}

	return false;
}

bool ruiOverlayManager::InjectTouchDown(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchDown(touch);
	}

	return false;
}

bool ruiOverlayManager::InjectTouchMove(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchMove(touch);
	}

	return false;
}

bool ruiOverlayManager::InjectTouchUp(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchUp(touch);
	}

	return false;
}

bool ruiOverlayManager::InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseDownEvent(button, mouse);
	}

	return false;
}

bool ruiOverlayManager::InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseUpEvent(button, mouse);
	}

	return false;
}

bool ruiOverlayManager::InjectMouseMotionEvent(const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseMotionEvent(mouse);
	}

	return false;
}

bool ruiOverlayManager::InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseWheelEvent(direction, mouse);
	}

	return false;
}

ruiOverlay* ruiOverlayManager::GetOverlay(rViewport* viewport) const{
	ruiViewportOverlayMap::const_iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end())
		return result->second;
	else
		return NULL;
}