#include "ui/ruiOverlay.hpp"

ruiOverlay::ruiOverlay(){
	m_activeWidget = NULL;
}

void ruiOverlay::AddWidget(ruiWidget* widget){
	m_widgets.push_back(widget);
}

ruiWidget* ruiOverlay::GetWidget(const rString& id){
	for (size_t i = 0; i < m_widgets.size(); i++){
		if (m_widgets[i]->Id() == id)
			return m_widgets[i];
	}

	return NULL;
}

void ruiOverlay::Update(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Update(engine);
}

void ruiOverlay::Draw(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Draw(engine);
}

void ruiOverlay::Clear(){
	for (size_t i = 0; i < m_widgets.size(); i++)
		delete m_widgets[i];
	
	m_widgets.clear();
}

ruiWidget* ruiOverlay::ActiveWidget() const{
	return m_activeWidget;
}

void ruiOverlay::ActivateWidget(ruiWidget* widget){
	m_activeWidget = widget;
}

ruiWidget* ruiOverlay::SelectWidget(const rPoint& position){
	rRect boundingBox;

	for (size_t i = 0; i < m_widgets.size(); i++){
		boundingBox = m_widgets[i]->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			return m_widgets[i];
		}
	}

	return NULL;
}
