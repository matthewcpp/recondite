#include "ui/ruiOverlayLoader.hpp"

ruiOverlayLoader::ruiParseItemMap ruiOverlayLoader::s_parseItemMap;

ruiOverlayLoader::ruiOverlayLoader(rEngine* engine){
	m_engine = engine;

	InitParseItemMap();
}

void ruiOverlayLoader::InitParseItemMap(){
	if (s_parseItemMap.size() > 0) return;

	s_parseItemMap["stylesheet"] = &ruiOverlayLoader::ParseStylesheetItem;
	s_parseItemMap["absolutelayout"] = &ruiOverlayLoader::ParseAbsoluteLayoutItem;
	s_parseItemMap["linearlayout"] = &ruiOverlayLoader::ParseLinearLayoutItem;
	s_parseItemMap["text"] = &ruiOverlayLoader::ParseTextItem;
	s_parseItemMap["picker"] = &ruiOverlayLoader::ParsePickerItem;
	s_parseItemMap["checkbox"] = &ruiOverlayLoader::ParseCheckboxItem;
	s_parseItemMap["button"] = &ruiOverlayLoader::ParseButtonItem;
}

void ruiOverlayLoader::Reset(){
	m_currentOverlay = NULL;

	m_path.clear();
	m_error.clear();
	m_layoutStack.clear();
}

ruiOverlayLoader::ruiParseItemMethod ruiOverlayLoader::GetParseItemMethod (const rString& itemName){
	rString item = itemName;
	
	for (size_t i =0; i < itemName.size(); i++)
		item[i] = tolower(itemName[i]);

	if (s_parseItemMap.count(item))
		return s_parseItemMap[item];
	else
		return NULL;
}

ruiOverlay* ruiOverlayLoader::ParseOverlay(const rString& path, rViewport* viewport){
	Reset();

	rXMLDocument document;
	rXMLReaderError error = document.LoadFromFile(path);

	rXMLElement* root = document.GetRoot();
	if (!root) return NULL;

	m_currentOverlay = new ruiOverlay(m_engine, viewport);
	m_path = path;

	ParseChildItems(root);

	return m_currentOverlay;
}

void ruiOverlayLoader::ParseChildItems(rXMLElement* parent){
	for (size_t i = 0; i < parent->NumChildren(); i++){
		rXMLElement* element = parent->GetChild(i);
		ruiParseItemMethod method = GetParseItemMethod(element->Name());

		if (method){ 
			(*this.*method)(element);
		}

	}
}

void ruiOverlayLoader::ParseStylesheetItem(rXMLElement* element){
	rString pathName = element->Text();
	
	rString dir = rPath::Directory(m_path);
	rString stylesheetPath = rPath::Combine(dir, pathName);

	auto cssFile = m_engine->content->FileSystem()->GetReadFileRef(stylesheetPath);
	
	if (cssFile)
		m_currentOverlay->Styles()->ParseStylesheet(*cssFile);
}

void ruiOverlayLoader::ParseAbsoluteLayoutItem(rXMLElement* element){
	int top = 0;
	int left = 0;

	element->GetAttribute<int>("top", top);
	element->GetAttribute<int>("left", left);

	ruiAbsoluteLayout* absoluteLayout = new ruiAbsoluteLayout();
	absoluteLayout->SetTop(top);
	absoluteLayout->SetLeft(left);

	if (m_layoutStack.size() == 0)
		m_currentOverlay->SetLayout(absoluteLayout);

	m_layoutStack.push_back(absoluteLayout);

	ParseChildItems(element);

	m_layoutStack.pop_back();
}

void ruiOverlayLoader::ParseTextItem(rXMLElement* element){
	rString id = m_currentOverlay->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiText* text = new ruiText(element->Text(), id, m_currentOverlay, m_engine);
	ParseClassList(element, text);

	m_layoutStack.back()->AddItem(text);
	m_currentOverlay->AddWidget(text);
}

void ruiOverlayLoader::ParsePickerItem(rXMLElement* element){
	rString id = m_currentOverlay->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	rArrayString options;

	size_t optionCount = element->NumChildren();
	for (size_t i =0; i < optionCount; i++){
		options.push_back(element->GetChild(i)->Text());
	}

	ruiPicker* picker = new ruiPicker(options, id, m_currentOverlay, m_engine);
	ParseClassList(element, picker);

	m_layoutStack.back()->AddItem(picker);
	m_currentOverlay->AddWidget(picker);
}

void ruiOverlayLoader::ParseCheckboxItem(rXMLElement* element){
	rString id = m_currentOverlay->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiCheckbox* checkbox = new ruiCheckbox(id, m_currentOverlay, m_engine);

	rString checked;
	if (element->GetAttribute<rString>("checked", checked))
		checkbox->SetChecked(checked == "checked");

	ParseClassList(element, checkbox);

	m_layoutStack.back()->AddItem(checkbox);
	m_currentOverlay->AddWidget(checkbox);
}

void ruiOverlayLoader::ParseButtonItem(rXMLElement* element){
	rString id = m_currentOverlay->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiButton* button = new ruiButton(element->Text(), id, m_currentOverlay, m_engine);

	ParseClassList(element, button);

	m_layoutStack.back()->AddItem(button);
	m_currentOverlay->AddWidget(button);
}

void ruiOverlayLoader::ParseClassList(rXMLElement* element, ruiWidget* widget){
	rString classList;
	if (element->GetAttribute<rString>("class", classList)){
		rIStringStream stream(classList);
		rString currentClass;

		while (stream){
			currentClass.clear();
			stream >> currentClass;

			if (currentClass.length())
				widget->AddClass(currentClass);
		}
	}
}

void ruiOverlayLoader::ParseLinearLayoutItem(rXMLElement* element){
	ruiLayoutDirection layoutDirection = ruiLAYOUT_HORIZONTAL;

	rString direction;
	if (element->GetAttribute<rString>("direction", direction)){
		if (direction == "vertical")
			layoutDirection = ruiLAYOUT_VERTICAL;
	}

	ruiLinearLayout* linearLayout = new ruiLinearLayout(layoutDirection);

	if (m_layoutStack.size() == 0)
		m_currentOverlay->SetLayout(linearLayout);

	m_layoutStack.push_back(linearLayout);

	ParseChildItems(element);

	m_layoutStack.pop_back();
}
