#include "ui/ruiPicker.hpp"

ruiPicker::ruiPicker(const rString& id, rEngine* engine)
:ruiWidget(id, engine)
{
	m_selectionIndex = 0;

	Bind(ruiEVT_MENU, this, &ruiPicker::OnSubmenuSelection);
}

ruiPicker::ruiPicker(rArrayString& options, const rString& id, rEngine* engine)
:ruiWidget(id, engine)
{
	m_selectionIndex = 0;
	SetOptions(options);
}

bool ruiPicker::OnPointerDown(const rPoint& position){
	ShowOptionsMenu();

	return true;
}

void ruiPicker::ShowOptionsMenu(){
	rRect boundingBox = BoundingBox();
	ruiMenu* menu = new ruiMenu();

	for (int i = 0; i < m_options.size(); i++)
		menu->AppendItem(i, m_options[i]);

	m_engine->ui->ShowContextMenu(menu, rPoint(boundingBox.Left(), boundingBox.Bottom() + 3), this);
}

rSize ruiPicker::ComputeSize() const{
	rFont* font = m_engine->content->GetFontAsset("consolas");
	rSize computedSize(0,0);

	if (font){
		for (size_t i = 0; i < m_options.size(); i++){
			rSize size =  font->MeasureString(m_options[i]);

			if (size.x > computedSize.x)
				computedSize = size;
		}
	}

	return computedSize;
}

void ruiPicker::Draw(rEngine& engine){
	rRect box = BoundingBox();
	rColor gray(200,200,200,255);
	engine.renderer->RenderRect(box, gray);
	

	rFont* font = engine.content->GetFontAsset("consolas");
	
	if (font){
		rString text = SelectionText();
		rPoint point (m_position.x + 5 , m_position.y + 5);
		rColor black(0,0,0,255);
		
		engine.renderer->RenderString(text,font, box, black);
	}

}

void ruiPicker::AddOption(const rString& option){
	m_options.push_back(option);
}

void ruiPicker::SetOptions(const rArrayString& options){
	m_selectionIndex = 0;
	m_options = options;
}

size_t ruiPicker::NumOptions() const{
	return m_options.size();
}

size_t ruiPicker::SelectionIndex() const{
	return m_selectionIndex;
}

bool ruiPicker::SetSelectionIndex(size_t index){
	if (index < m_options.size()){
		m_selectionIndex = index;

		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_PICKER_CHANGE, event);

		return true;
	}
	else{
		return false;
	}
}

rString ruiPicker::SelectionText() const{
	if (m_options.size() > 0){
		return m_options[m_selectionIndex];
	}
	else{
		return "";
	}
}

void ruiPicker::Clear(){
	m_selectionIndex = 0;
	m_options.clear();
}

const rArrayString& ruiPicker::Options() const{
	return m_options;
}

void ruiPicker::OnSubmenuSelection(rEvent& event){
	ruiMenuEvent& menuEvent = static_cast<ruiMenuEvent&> (event);

	SetSelectionIndex(menuEvent.Selection());
}

rString ruiPicker::GetWidgetType() const{
	return "picker";
}

