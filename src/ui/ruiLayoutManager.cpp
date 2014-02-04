#include "ui/ruiLayoutManager.hpp"

ruiLayoutManager::ruiLayoutManager(){

}

ruiLayoutManager::~ruiLayoutManager(){
	Clear();
}

ruiOverlay* ruiLayoutManager::CreateOverlay(rViewport* viewport){
	ruiViewportOverlayMap::iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end()){
		delete result->second;
	}

	ruiOverlay* overlay = new ruiOverlay();
	m_overlays[viewport] = overlay;

	return overlay;
}

void ruiLayoutManager::Clear(){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		delete it->second;
	}

	m_overlays.clear();
}

rViewport* ruiLayoutManager::DetermineViewport(const rPoint& point){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		rRect screenRect = it->first->GetScreenRect();

		if (screenRect.ContainsPoint(point))
			return it->first;
	}

	return NULL;
}



void ruiLayoutManager::Update(rEngine& engine){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		it->second->Update(engine);
	}
}

void ruiLayoutManager::Draw(rEngine& engine){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		it->second->Draw(engine);
	}
}

bool ruiLayoutManager::InjectTouchDown(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchUp(touch);
	}

	return false;
}

bool ruiLayoutManager::InjectTouchMove(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchMove(touch);
	}

	return false;
}

bool ruiLayoutManager::InjectTouchUp(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectTouchUp(touch);
	}

	return false;
}

bool ruiLayoutManager::InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseDownEvent(button, mouse);
	}

	return false;
}

bool ruiLayoutManager::InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseUpEvent(button, mouse);
	}

	return false;
}

bool ruiLayoutManager::InjectMouseMotionEvent(const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseMotionEvent(mouse);
	}

	return false;
}

bool ruiLayoutManager::InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse){
	rPoint position = mouse.Position();

	rViewport* viewport = DetermineViewport(position);

	if (viewport && m_overlays.count(viewport)){
		return m_overlays[viewport]->InjectMouseWheelEvent(direction, mouse);
	}

	return false;
}