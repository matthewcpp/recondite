#include "ui/ruiPicker.hpp"

ruiPicker::ruiPicker(const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, engine, position, size)
{
	m_selectionIndex = 0;
}

ruiPicker::ruiPicker(rArrayString& options, const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, engine, position, size)
{
	m_selectionIndex = 0;
	SetOptions(options);
}

void ruiPicker::OnPointerDown(const rPoint& position){
	ShowOptionsMenu();
}

void ruiPicker::ShowOptionsMenu(){
	ruiPickerOptionsMenu* optionsMenu = new ruiPickerOptionsMenu(this, "-1", m_engine);
	optionsMenu->SetPosition(m_position.x, m_position.y + m_size.y + 20);
	optionsMenu->SetSize(250, NumOptions() * 30);

	ShowModal(optionsMenu);
}

void ruiPicker::Draw(rEngine& engine){
	rRect box(m_position, m_size);
	rColor gray(200,200,200,255);
	engine.renderer->RenderRect(box, gray);
	

	rFont* font = engine.content->GetFontAsset("consolas");
	
	if (font){
		rString text = SelectionText();
		rPoint point (m_position.x + 5 , m_position.y + 5);
		rColor black(0,0,0,255);
		
		engine.renderer->RenderString(text,font, point, black);
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

		Trigger(ruiEVENT_PICKER_CHANGE);

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

void ruiPicker::SubmenuSelection(size_t index){
	SetSelectionIndex(index);
}
