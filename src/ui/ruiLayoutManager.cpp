#include "ui/ruiLayoutManager.hpp"

ruiLayoutManager::ruiLayoutManager(){
	m_activeWidget = NULL;
}
ruiLayoutManager::~ruiLayoutManager(){
	Clear();
}

bool ruiLayoutManager::InjectTouchDown(const rTouch& touch){
	rRect boundingBox;
	rPoint currentTouchPos = touch.GetCurrentPosition();
	
	for (size_t i = 0; i < m_widgets.size(); i++){
		boundingBox = m_widgets[i]->BoundingBox();
		
		if (boundingBox.ContainsPoint(currentTouchPos)){
			m_activeWidget = m_widgets[i];
			break;
		}
	}
	
	if (m_activeWidget){
		m_activeWidget->OnTouchDown(touch);
		return true;
	}
	else{
		return false;
	}
}

bool ruiLayoutManager::InjectTouchMove(const rTouch& touch){
	if (m_activeWidget){
		m_activeWidget->OnTouchMove(touch);
		return true;
	}
	else{
		return false;
	}
}

bool ruiLayoutManager::InjectTouchUp(const rTouch& touch){
	if (m_activeWidget){
		m_activeWidget->OnTouchUp(touch);
		return true;
	}
	else{
		return false;
	}
}

void ruiLayoutManager::Update(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Update(engine);
	
}
void ruiLayoutManager::Draw(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Draw(engine);
}

void ruiLayoutManager::AddWidget(ruiWidget* widget){
	m_widgets.push_back(widget);
}

void ruiLayoutManager::Clear(){
	for (size_t i = 0; i < m_widgets.size(); i++)
		delete m_widgets[i];
	
	m_widgets.clear();
}

void ruiLayoutManager::OnTouchEvent(const rTouch& touch){
	switch(touch.GetType()){
	case rTOUCH_DOWN:
		InjectTouchDown(touch);
		break;

	case rTOUCH_MOVE:
		InjectTouchMove(touch);
		break;

	case rTOUCH_CANCEL:
	case rTOUCH_UP:
		InjectTouchUp(touch);
		break;
	}
}
