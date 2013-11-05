#include "ui/ruiLayoutManager.hpp"

ruiLayoutManager::ruiLayoutManager(){
	m_activeWidget = NULL;
	m_modalWidget = NULL;
}
ruiLayoutManager::~ruiLayoutManager(){
	Clear();
}

bool ruiLayoutManager::InjectTouchDown(const rTouch& touch){
	rRect boundingBox;
	rPoint currentTouchPos = touch.GetCurrentPosition();
	
	if (m_modalWidget){
		boundingBox = m_modalWidget->BoundingBox();

		if (boundingBox.ContainsPoint(currentTouchPos)){
			m_modalWidget->OnTouchDown(touch);
		}
		return true;
	}
	else{
		for (size_t i = 0; i < m_widgets.size(); i++){
			boundingBox = m_widgets[i]->BoundingBox();

			if (boundingBox.ContainsPoint(currentTouchPos)){
				m_activeWidget = m_widgets[i];
				m_activeWidget->OnTouchDown(touch);
				return true;
			}
		}
	}

	return false;
}

bool ruiLayoutManager::InjectTouchMove(const rTouch& touch){
	if (m_modalWidget){
		m_modalWidget->OnTouchMove(touch);
		return true;
	}
	else if (m_activeWidget){
		m_activeWidget->OnTouchMove(touch);
		return true;
	}
	else{
		return false;
	}
}

bool ruiLayoutManager::InjectTouchUp(const rTouch& touch){
	if (m_modalWidget){
		m_modalWidget->OnTouchUp(touch);
		return true;
	}
	else if (m_activeWidget){
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
	
	if (m_modalWidget){
		m_modalWidget->Update(engine);
	}

}
void ruiLayoutManager::Draw(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Draw(engine);

	if (m_modalWidget){
		m_modalWidget->Draw(engine);
	}
}

void ruiLayoutManager::AddWidget(ruiWidget* widget){
	m_widgets.push_back(widget);
}

ruiWidget* ruiLayoutManager::GetWidget(int id){
	for (size_t i = 0; i < m_widgets.size(); i++){
		if (m_widgets[i]->Id() == id)
			return m_widgets[i];
	}

	return NULL;
}

void ruiLayoutManager::Clear(){
	for (size_t i = 0; i < m_widgets.size(); i++)
		delete m_widgets[i];
	
	m_widgets.clear();

	ShowModal(NULL);
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

void ruiLayoutManager::ShowModal(ruiWidget* widget){
	if (m_modalWidget)
		delete m_modalWidget;

	m_modalWidget = widget;
}

void ruiLayoutManager::EndModal(ruiWidget* widget){
	if (m_modalWidget == widget){
		delete m_modalWidget;
		m_modalWidget = NULL;
	}
}
