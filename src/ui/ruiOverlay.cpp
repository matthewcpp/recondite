#include "ui/ruiOverlay.hpp"

ruiOverlay::ruiOverlay(){
	m_activeWidget = NULL;
	m_modalWidget = NULL;
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
	
	if (m_modalWidget){
		m_modalWidget->Update(engine);
	}

}
void ruiOverlay::Draw(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Draw(engine);

	if (m_modalWidget){
		m_modalWidget->Draw(engine);
	}
}

void ruiOverlay::Clear(){
	for (size_t i = 0; i < m_widgets.size(); i++)
		delete m_widgets[i];
	
	m_widgets.clear();

	ShowModal(NULL);
}

void ruiOverlay::ShowModal(ruiWidget* widget){
	if (m_modalWidget)
		delete m_modalWidget;

	m_modalWidget = widget;
}

void ruiOverlay::EndModal(ruiWidget* widget){
	if (m_modalWidget == widget){
		delete m_modalWidget;
		m_modalWidget = NULL;
	}
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
