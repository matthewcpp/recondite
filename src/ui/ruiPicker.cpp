#include "ui/ruiPicker.hpp"

#include "ui/ruiDocument.hpp"

ruiPicker::ruiPicker(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
{
	Init();
}

ruiPicker::ruiPicker(rArrayString& options, const rString& id, ruiIDocument* document, rEngine* engine)
	: ruiWidget(id, document, engine)
{
	Init();
	SetOptions(options);
}

void ruiPicker::Init(){
	m_selectionIndex = 0;
	Bind(ruiEVT_MENU, this, &ruiPicker::OnSubmenuSelection);
}

bool ruiPicker::OnPointerDown(const rPoint& position){
	ShowOptionsMenu();

	return true;
}

void ruiPicker::ShowOptionsMenu(){
	rRect boundingBox = BoundingBox();
	ruiMenu* menu = new ruiMenu();

	for (size_t i = 0; i < m_options.size(); i++)
		menu->AppendItem(i, m_options[i]);

	m_document->ShowContextMenu(menu, ComputedStyle(), rPoint(boundingBox.Left(), boundingBox.Bottom() + 3), this);
}

rSize ruiPicker::ComputeSize(){
	Font::Face* font = DetermineFont();
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

void ruiPicker::Draw(){
	ruiStyle* style = ComputedStyle();

	rColor color(255, 255, 255, 255);
	rRect boundingBox = BoundingBox();

	RenderWidgetBase(style, boundingBox);

	Font::Face* font = DetermineFont();

	if (font){
		color.Set(255, 255, 255, 255);
		style->GetColor("color", color);

		m_engine->renderer->SpriteBatch()->RenderString(SelectionText(), font, ContentPosition(), color, 0.01);
	}
}

void ruiPicker::AddOption(const rString& option){
	m_options.push_back(option);
	InvalidateSize();
}

void ruiPicker::SetOptions(const rArrayString& options){
	m_selectionIndex = 0;
	m_options = options;
	InvalidateSize();
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

