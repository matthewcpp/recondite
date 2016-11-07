#include "ui/ruiLayout.hpp"
#include "ui/ruiDocument.hpp"

//--------------------

ruiLayout::ruiLayout(const rString& id, ruiIDocument* document, rEngine* engine) 
	:ruiWidget(id, document, engine)
{}

void ruiLayout::Clear(){
	m_layoutItems.clear();
}

void ruiLayout::AddItem(ruiWidget* widget){
	m_layoutItems.push_back(widget);
	widget->SetParent(this);
	InvalidateSize();
}

size_t ruiLayout::ItemCount() const{
	return m_layoutItems.size();
}

rSize ruiLayout::ComputeSize() {
	rSize contentSize(0, 0);

	for (size_t i = 0; i < m_layoutItems.size(); i++) {
		rSize itemSize = m_layoutItems[i]->Size();
		contentSize.Set(std::max(contentSize.x, itemSize.x), std::max(contentSize.y, itemSize.y));
	}

	return contentSize;
}

ruiWidget* ruiLayout::GetItem(size_t index) {
	return m_layoutItems[index];
}

void ruiLayout::Update() {
	for (size_t i = 0; i < m_layoutItems.size(); i++)
		m_layoutItems[i]->Update();
}

void ruiLayout::Draw() {
	RenderWidgetBase(ComputedStyle(), BoundingBox());

	for (size_t i = 0; i < m_layoutItems.size(); i++)
		m_layoutItems[i]->Draw();
}

void ruiLayout::ChildUpdated(ruiWidget* child) {
	InvalidateSize();
}