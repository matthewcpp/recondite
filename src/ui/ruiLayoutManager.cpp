#include "ui/ruiLayoutManager.hpp"

ruiLayoutManager::ruiLayoutManager(){
	m_activeWidget = NULL;
	m_modalWidget = NULL;

	ruiWidget::widgetManager = this;
}
ruiLayoutManager::~ruiLayoutManager(){
	Clear();
}

ruiWidget* ruiLayoutManager::SelectWidget(const rPoint& position){
	rRect boundingBox;

	for (size_t i = 0; i < m_widgets.size(); i++){
		boundingBox = m_widgets[i]->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			return m_widgets[i];
		}
	}

	return NULL;
}

bool ruiLayoutManager::InjectTouchDown(const rTouch& touch){
	rPoint currentTouchPos = touch.GetCurrentPosition();
	
	if (m_modalWidget){
		rRect boundingBox = m_modalWidget->BoundingBox();

		if (boundingBox.ContainsPoint(currentTouchPos)){
			m_modalWidget->OnTouchDown(touch);
		}
		return true;
	}
	else{
		ruiWidget* widget = SelectWidget(currentTouchPos);

		if (widget){
			m_activeWidget = widget;
			m_activeWidget->OnTouchDown(touch);
			return true;
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

bool ruiLayoutManager::InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse){
	rPoint position = mouse.Position();
	
	if (m_modalWidget){
		rRect boundingBox = m_modalWidget->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			m_modalWidget->MouseDownEvent(button, mouse);
		}
		return true;
	}
	else{
		ruiWidget* widget = SelectWidget(position);

		if (widget){
			m_activeWidget = widget;
			m_activeWidget->MouseDownEvent(button, mouse);
			return true;
		}
	}

	return false;
}

bool ruiLayoutManager::InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse){
	if (m_modalWidget){
		m_modalWidget->MouseUpEvent(button, mouse);
		return true;
	}
	else if (m_activeWidget){
		m_activeWidget->MouseUpEvent(button, mouse);
		return true;
	}
	else{
		return false;
	}
}

bool ruiLayoutManager::InjectMouseMotionEvent(const rMouseState& mouse){
	if (m_modalWidget){
		m_modalWidget->OnMouseMotion(mouse);
		return true;
	}
	else if (m_activeWidget){
		m_activeWidget->OnMouseMotion(mouse);
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

rContentError ruiLayoutManager::LoadOverlay(const rString& path){
	return rCONTENT_ERROR_NONE;
}
