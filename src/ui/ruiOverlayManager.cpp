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
	m_styleManager.Clear();
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

ruiOverlay* ruiOverlayManager::DetermineOverlay(const rPoint& point){
	rViewport* viewport = DetermineViewport(point);

	if (viewport && m_overlays.count(viewport))
		return m_overlays[viewport];
	else
		return NULL;
}

ruiOverlay* ruiOverlayManager::GetOverlay(rViewport* viewport) const{
	ruiViewportOverlayMap::const_iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end())
		return result->second;
	else
		return NULL;
}

ruiStyleManager* ruiOverlayManager::Styles(){
	return &m_styleManager;
}

void ruiOverlayManager::Update(rEngine& engine){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		m_activeOverlay = it->second;
		it->second->Update(engine);
	}

	m_activeOverlay = NULL;
}

void ruiOverlayManager::Draw(rViewport* viewport, rEngine& engine){
	ruiViewportOverlayMap::iterator vp = m_overlays.find(viewport);

	if (vp != m_overlays.end()){
		m_activeOverlay = vp->second;
		vp->second->Draw(engine);
	}

	m_activeOverlay = NULL;
}

bool ruiOverlayManager::InsertKeyEvent(rKey key, rKeyState state){
	return false;
}

bool ruiOverlayManager::InsertTouchEvent(int id, const rPoint& position, rTouchType type){
	return false;
}

bool ruiOverlayManager::InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position){
	if (state == rBUTTON_STATE_DOWN)
		return ProcessMouseDown(button, position);
	else
		return ProcessMouseUp(button, position);
}

bool ruiOverlayManager::ProcessMouseDown(rMouseButton button, const rPoint& position){
	ruiMouseEvent event(button, rBUTTON_STATE_DOWN, position);

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){		
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			activeWidget->Trigger(ruiEVT_MOUSE_DOWN, event);
		}
	}

	return false;
}

bool ruiOverlayManager::InsertMouseMotionEvent(const rPoint& position){
	ruiMouseEvent event(position);

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			rRect boundingBox = activeWidget->BoundingBox();

			if (boundingBox.ContainsPoint(position)){
				activeWidget->Trigger(ruiEVT_MOUSE_MOTION, event);
			}
			else{
				activeWidget->Trigger(ruiEVT_MOUSE_LEAVE, event);
				overlay->ActivateWidget(NULL);
			}
		}
		else {
			ruiWidget* selectedWidget = overlay->SelectWidget(position);

			if (selectedWidget){
				selectedWidget->Trigger(ruiEVT_MOUSE_ENTER, event);
				overlay->ActivateWidget(selectedWidget);
			}
		}

	}

	return false;
}

bool ruiOverlayManager::ProcessMouseUp(rMouseButton button, const rPoint& position){
	ruiMouseEvent event(button, rBUTTON_STATE_UP, position);

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			activeWidget->Trigger(ruiEVT_MOUSE_UP, event);
		}
	}

	return false;
}


bool ruiOverlayManager::InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction){
	ruiMouseEvent event(direction, position);

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			activeWidget->Trigger(ruiEVT_MOUSE_WHEEL, event);
		}
	}

	return false;
}

bool ruiOverlayManager::ShowContextMenu(const ruiMenu* menu, const rPoint& position, rEventHandler* handler){
	return false;
}

void ruiOverlayManager::CancelContextMenu(){
}