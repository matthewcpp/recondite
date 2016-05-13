#include "ui/ruiManager.hpp"
#include "ui/ruiOverlayLoader.hpp"

ruiManager::ruiManager(rEngine* engine){
	m_engine = engine;
}

ruiManager::~ruiManager(){
	Clear();
}

ruiOverlay* ruiManager::CreateOverlay(rViewport* viewport){

	ruiOverlay* overlay = new ruiOverlay(m_engine, viewport);
	AddOverlayToViewport(overlay, viewport);

	return overlay;
}

ruiOverlay* ruiManager::LoadOverlay(const rString& filePath, rViewport* viewport){
	ruiOverlayLoader loader(m_engine);
	ruiOverlay* overlay = loader.ParseOverlay(filePath, viewport);

	if (overlay){
		AddOverlayToViewport(overlay, viewport);
		overlay->UpdateLayout(true);
		return overlay;
	}
	else {
		return NULL;
	}
}

void ruiManager::AddOverlayToViewport(ruiOverlay* overlay, rViewport* viewport){
	ruiViewportOverlayMap::iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end()){
		delete result->second;
	}
	m_overlays[viewport] = overlay;
}

void ruiManager::Clear(){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		delete it->second;
	}

	m_overlays.clear();
}

rViewport* ruiManager::DetermineViewport(const rPoint& point){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		rRect screenRect = it->first->GetScreenRect();

		if (screenRect.ContainsPoint(point))
			return it->first;
	}

	return NULL;
}

ruiOverlay* ruiManager::DetermineOverlay(const rPoint& point){
	rViewport* viewport = DetermineViewport(point);

	if (viewport && m_overlays.count(viewport))
		return m_overlays[viewport];
	else
		return NULL;
}

ruiOverlay* ruiManager::GetOverlay(rViewport* viewport) const{
	ruiViewportOverlayMap::const_iterator result = m_overlays.find(viewport);

	if (result != m_overlays.end())
		return result->second;
	else
		return NULL;
}

void ruiManager::Update(){
	ruiViewportOverlayMap::iterator end = m_overlays.end();

	for (ruiViewportOverlayMap::iterator it = m_overlays.begin(); it != end; ++it){
		m_activeOverlay = it->second;
		it->second->Update();
	}

	m_activeOverlay = NULL;
}

void ruiManager::Draw(rViewport* viewport){
	ruiViewportOverlayMap::iterator end = m_overlays.end();
	ruiViewportOverlayMap::iterator vp = m_overlays.find(viewport);

	if (m_overlays.count(viewport)){
		m_activeOverlay = m_overlays[viewport];
		m_activeOverlay->Draw();
	}

	m_activeOverlay = NULL;
}
bool ruiManager::InsertKeyEvent(rKey key, rKeyState state){
	return false;
}

bool ruiManager::InsertTouchEvent(int id, const rPoint& position, rTouchType type){
	return false;
}

bool ruiManager::InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position){
	if (state == rBUTTON_STATE_DOWN)
		return ProcessMouseDown(button, position);
	else if (state ==rBUTTON_STATE_UP)
		return ProcessMouseUp(button, position);
	else
		return false;
}

bool ruiManager::ProcessMouseDown(rMouseButton button, const rPoint& position){
	ruiMouseEvent event(button, rBUTTON_STATE_DOWN, position);
	//m_menuManager.Trigger(ruiEVT_MOUSE_DOWN, event);

	if (event.Handled())
		return true;

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){		
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			activeWidget->Trigger(ruiEVT_MOUSE_DOWN, event);
			activeWidget->UiState("active");
		}
	}

	return false;
}

bool ruiManager::InsertMouseMotionEvent(const rPoint& position){
	ruiMouseEvent event(position);
	//m_menuManager.Trigger(ruiEVT_MOUSE_MOTION, event);

	if (event.Handled())
		return true;

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			rRect boundingBox = activeWidget->BoundingBox();

			if (boundingBox.ContainsPoint(position)){
				activeWidget->Trigger(ruiEVT_MOUSE_MOTION, event);
			}
			else if (activeWidget->UiState() == "hover"){
				activeWidget->Trigger(ruiEVT_MOUSE_LEAVE, event);
				activeWidget->UiState("");
				overlay->ActivateWidget(NULL);
			}
		}
		else {
			ruiWidget* selectedWidget = overlay->SelectWidget(position);

			if (selectedWidget){
				selectedWidget->Trigger(ruiEVT_MOUSE_ENTER, event);
				selectedWidget->UiState("hover");
				overlay->ActivateWidget(selectedWidget);
			}
		}

	}

	return false;
}

bool ruiManager::ProcessMouseUp(rMouseButton button, const rPoint& position){
	ruiMouseEvent event(button, rBUTTON_STATE_UP, position);
	//m_menuManager.Trigger(ruiEVT_MOUSE_UP, event);

	if (event.Handled())
		return true;

	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiWidget* activeWidget = overlay->ActiveWidget();

		if (activeWidget){
			rRect boundingBox = activeWidget->BoundingBox();
			activeWidget->Trigger(ruiEVT_MOUSE_UP, event);

			if (boundingBox.ContainsPoint(position))
				activeWidget->UiState("hover");
			else{
				activeWidget->UiState("");
				overlay->ActivateWidget(NULL);
			}
		}
	}

	return false;
}


bool ruiManager::InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction){
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