#include "ui/ruiDocumentLoader.hpp"

#include "ui/ruiManager.hpp"

#include "stream/rIStringStream.hpp"

#include "ui/ruiAbsoluteLayout.hpp"
#include "ui/ruiLinearLayout.hpp"
#include "ui/ruiText.hpp"
#include "ui/ruiTextBox.hpp"
#include "ui/ruiPicker.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiLogText.hpp"

ruiDocumentLoader::ruiParseItemMap ruiDocumentLoader::s_parseItemMap;

ruiDocumentLoader::ruiDocumentLoader(ruiManager* manager, rEngine* engine){
	m_engine = engine;
	m_manager = manager;

	InitParseItemMap();
}

void ruiDocumentLoader::InitParseItemMap(){
	if (s_parseItemMap.size() > 0) return;

	s_parseItemMap["stylesheet"] = &ruiDocumentLoader::ParseStylesheetItem;
	s_parseItemMap["absolutelayout"] = &ruiDocumentLoader::ParseAbsoluteLayoutItem;
	s_parseItemMap["linearlayout"] = &ruiDocumentLoader::ParseLinearLayoutItem;
	s_parseItemMap["text"] = &ruiDocumentLoader::ParseTextItem;
	s_parseItemMap["textbox"] = &ruiDocumentLoader::ParseTextBoxItem;
	s_parseItemMap["logtext"] = &ruiDocumentLoader::ParseLogTextItem;
	s_parseItemMap["picker"] = &ruiDocumentLoader::ParsePickerItem;
	s_parseItemMap["checkbox"] = &ruiDocumentLoader::ParseCheckboxItem;
	s_parseItemMap["button"] = &ruiDocumentLoader::ParseButtonItem;
	s_parseItemMap["slider"] = &ruiDocumentLoader::ParseSliderItem;
	s_parseItemMap["controller"] = &ruiDocumentLoader::ParseControllerItem;
}

void ruiDocumentLoader::Reset(){
	m_currentDocument = NULL;

	m_path.clear();
	m_error.clear();
	m_layoutStack.clear();
}

ruiDocumentLoader::ruiParseItemMethod ruiDocumentLoader::GetParseItemMethod (const rString& itemName){
	rString item = itemName;
	
	for (size_t i =0; i < itemName.size(); i++)
		item[i] = tolower(itemName[i]);

	if (s_parseItemMap.count(item))
		return s_parseItemMap[item];
	else
		return NULL;
}

ruiDocument* ruiDocumentLoader::LoadDocument(const rString& path, rViewport* viewport){
	Reset();

	rXMLDocument document;
	rXMLReaderError error = document.LoadFromFile(path);

	rXMLElement* root = document.GetRoot();
	if (!root) return NULL;

	m_currentDocument = new ruiDocument(m_engine, viewport);
	m_path = path;

	ParseChildItems(root);

	return m_currentDocument;
}

void ruiDocumentLoader::ParseChildItems(rXMLElement* parent){
	for (size_t i = 0; i < parent->NumChildren(); i++){
		rXMLElement* element = parent->GetChild(i);
		ruiParseItemMethod method = GetParseItemMethod(element->Name());

		if (method){ 
			(*this.*method)(element);
		}
		else{
			ParseChildItems(element);
		}
	}
}

void ruiDocumentLoader::ParseStylesheetItem(rXMLElement* element){
	rString pathName = element->Text();
	
	rString dir = rPath::Directory(m_path);
	rString stylesheetPath = rPath::Combine(dir, pathName);

	auto cssFile = m_engine->content->FileSystem()->GetReadFileRef(stylesheetPath);
	
	if (cssFile)
		m_currentDocument->Styles()->ParseStylesheet(*cssFile);
}

void ruiDocumentLoader::ParseAbsoluteLayoutItem(rXMLElement* element){
	int top = 0;
	int left = 0;

	element->GetAttribute<int>("top", top);
	element->GetAttribute<int>("left", left);

	ruiAbsoluteLayout* absoluteLayout = new ruiAbsoluteLayout();
	absoluteLayout->SetTop(top);
	absoluteLayout->SetLeft(left);

	if (m_layoutStack.size() == 0)
		m_currentDocument->SetLayout(absoluteLayout);
	else
		m_layoutStack.back()->AddItem(absoluteLayout);

	m_layoutStack.push_back(absoluteLayout);

	ParseChildItems(element);

	m_layoutStack.pop_back();
}

void ruiDocumentLoader::ParseLinearLayoutItem(rXMLElement* element){
	ruiLayoutDirection layoutDirection = ruiLAYOUT_HORIZONTAL;

	rString direction;
	if (element->GetAttribute<rString>("direction", direction)){
		if (direction == "vertical")
			layoutDirection = ruiLAYOUT_VERTICAL;
	}

	ruiLinearLayout* linearLayout = new ruiLinearLayout(layoutDirection);

	if (m_layoutStack.size() == 0)
		m_currentDocument->SetLayout(linearLayout);
	else
		m_layoutStack.back()->AddItem(linearLayout);

	m_layoutStack.push_back(linearLayout);

	ParseChildItems(element);

	m_layoutStack.pop_back();
}

void ruiDocumentLoader::ParseTextItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiText* text = new ruiText(element->Text(), id, m_currentDocument, m_engine);
	ParseClassList(element, text);

	m_layoutStack.back()->AddItem(text);
	m_currentDocument->AddWidget(text);
}

void ruiDocumentLoader::ParseTextBoxItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiTextBox* textbox = new ruiTextBox(element->Text(), id, m_currentDocument, m_engine);
	ParseClassList(element, textbox);

	m_layoutStack.back()->AddItem(textbox);
	m_currentDocument->AddWidget(textbox);
}

void ruiDocumentLoader::ParseLogTextItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiLogText* logText = new ruiLogText(id, m_currentDocument, m_engine);
	ParseClassList(element, logText);

	m_layoutStack.back()->AddItem(logText);
	m_currentDocument->AddWidget(logText);
}

void ruiDocumentLoader::ParsePickerItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	rArrayString options;

	size_t optionCount = element->NumChildren();
	for (size_t i =0; i < optionCount; i++){
		options.push_back(element->GetChild(i)->Text());
	}

	ruiPicker* picker = new ruiPicker(options, id, m_currentDocument, m_engine);
	ParseClassList(element, picker);

	m_layoutStack.back()->AddItem(picker);
	m_currentDocument->AddWidget(picker);
}

void ruiDocumentLoader::ParseCheckboxItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiCheckbox* checkbox = new ruiCheckbox(id, m_currentDocument, m_engine);

	rString checked;
	if (element->GetAttribute<rString>("checked", checked))
		checkbox->SetChecked(checked == "checked");

	ParseClassList(element, checkbox);

	m_layoutStack.back()->AddItem(checkbox);
	m_currentDocument->AddWidget(checkbox);
}

void ruiDocumentLoader::ParseSliderItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiSlider* slider = new ruiSlider(id, m_currentDocument, m_engine);

	float min, max, value;

	if (element->GetAttribute<float>("min", min) && element->GetAttribute<float>("max", max)){
		slider->SetValueRange(min, max);
	}

	if (element->GetAttribute<float>("value", value)){
		slider->SetValue(value);
	}

	ParseClassList(element, slider);

	m_layoutStack.back()->AddItem(slider);
	m_currentDocument->AddWidget(slider);
}

void ruiDocumentLoader::ParseButtonItem(rXMLElement* element){
	rString id = m_currentDocument->GetDefaultId();
	element->GetAttribute<rString>("id", id);

	ruiButton* button = new ruiButton(element->Text(), id, m_currentDocument, m_engine);

	ParseClassList(element, button);

	m_layoutStack.back()->AddItem(button);
	m_currentDocument->AddWidget(button);
}

void ruiDocumentLoader::ParseClassList(rXMLElement* element, ruiWidget* widget){
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

void ruiDocumentLoader::ParseControllerItem(rXMLElement* element){
	rString controllerType;
	if (element->GetAttribute("type", controllerType)){
		m_currentDocument->SetController(m_manager->CreateController(controllerType, m_currentDocument));
	}
		
}