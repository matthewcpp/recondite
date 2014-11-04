#include "ui/ruiOverlay.hpp"

ruiOverlay::ruiOverlay(rViewport* viewport){
	m_activeWidget = NULL;
	m_layout = NULL;
	m_viewport = viewport;
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
		m_widgets[i]->Update();

	UpdateLayout();
}

void ruiOverlay::UpdateLayout(bool force){
	if (m_layout){
            rRect layoutRect = m_viewport->GetScreenRect();
            m_layout->Layout(layoutRect);
        }
}

void ruiOverlay::Draw(rEngine& engine){
	for (size_t i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->Draw();
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

ruiLayout* ruiOverlay::Layout() const{
	return m_layout;
}

void ruiOverlay::SetLayout(ruiLayout* layout){
	if (m_layout)
		delete m_layout;
	
		m_layout = layout;
}

rString ruiOverlay::GetDefaultId () const{
	rOStringStream str("item");
	str << m_widgets.size();

	return str.Str();
}