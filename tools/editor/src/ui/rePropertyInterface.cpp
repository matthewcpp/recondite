#include "rePropertyInterface.hpp"

//rePropertyInterfaceBase

riSerializationTarget* rePropertyInterfaceBase::SubObject(const rString& name) {
	return this;
}

bool rePropertyInterfaceBase::Next(){
	return false;
}

bool rePropertyInterfaceBase::Category(const rString& name){
	return false;
}

//rePropertyUpdater

bool rePropertyUpdater::Boolean(const rString& name, bool& val) {
	wxString wxName = name.c_str();

	m_grid->SetPropertyValue(wxName, val);

	return true;
}

bool rePropertyUpdater::Int(const rString& name, int& val) {
	wxString wxName = name.c_str();

	m_grid->SetPropertyValue(wxName, val);

	return true;
}

bool rePropertyUpdater::Float(const rString& name, float& val) {
	wxString wxName = name.c_str();

	m_grid->SetPropertyValue(wxName, val);

	return true;
}

bool rePropertyUpdater::String(const rString& name, rString& val) {
	wxString wxName = name.c_str();
	wxString valString = val.c_str();

	m_grid->SetPropertyValue(wxName, valString);

	return true;
}

bool rePropertyUpdater::Vector3(const rString& name, rVector3& val) {
	wxString wxName = name.c_str();

	m_grid->SetPropertyValue(wxName + ".x", val.x);
	m_grid->SetPropertyValue(wxName + ".y", val.y);
	m_grid->SetPropertyValue(wxName + ".z", val.z);

	return true;
}

bool rePropertyUpdater::Color(const rString& name, rColor& color) {
	wxString wxName = name.c_str();
	wxColor wxc(color.red, color.green, color.blue, color.alpha);

	wxVariant variant;
	variant << wxc;

	m_grid->SetPropertyValue(wxName, variant);

	return true;
}

void rePropertyUpdater::Read(rActor3* actor){
	if (!actor) return;

	m_grid->Freeze();
	actor->Save(this);
	m_grid->Thaw();
}

rePropertyUpdater::rePropertyUpdater(wxPropertyGrid* grid){
	m_grid = grid;
}

//rePropertyReader

rePropertyReader::rePropertyReader(wxPropertyGrid* grid){
	m_grid = grid;
}

void rePropertyReader::Read(rActor3* actor){
	if (!actor) return;

	m_grid->Freeze();
	m_grid->Clear();
	actor->Save(this);
	m_grid->Thaw();
}

bool rePropertyReader::Boolean(const rString& name, bool& val) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxBoolProperty* property = new wxBoolProperty(displayName, wxName, val);

	wxString propertyInfo = wxString::Format("bool:%s", name.c_str());
	property->SetClientObject(new wxStringClientData(propertyInfo));

	m_grid->Append(property);

	return true;
}

bool rePropertyReader::Int(const rString& name, int& val) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxIntProperty* property = new wxIntProperty(displayName, wxName, val);

	wxString propertyInfo = wxString::Format("int:%s", name.c_str());
	property->SetClientObject(new wxStringClientData(propertyInfo));

	m_grid->Append(property);

	return true;
}

bool rePropertyReader::Float(const rString& name, float& val) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxFloatProperty* property = new wxFloatProperty(displayName, wxName, val);

	wxString propertyInfo = wxString::Format("float:%s", name.c_str());
	property->SetClientObject(new wxStringClientData(propertyInfo));

	m_grid->Append(property);

	return true;
}

bool rePropertyReader::String(const rString& name, rString& val) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxString wxValString = val.c_str();
	wxStringProperty* property = new wxStringProperty(displayName, wxName, wxValString);

	wxString propertyInfo = wxString::Format("string:%s", name.c_str());
	property->SetClientObject(new wxStringClientData(propertyInfo));

	m_grid->Append(property);

	return true;
}

bool rePropertyReader::Vector3(const rString& name, rVector3& val) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxString propertyInfo = wxString::Format("vector3:%s", name.c_str());
	
	wxFloatProperty* property = new wxFloatProperty(displayName + " X", wxName + ".x", val.x);
	property->SetClientObject(new wxStringClientData(propertyInfo));
	m_grid->Append(property);

	property = new wxFloatProperty(displayName + " Y", wxName + ".y", val.y);
	property->SetClientObject(new wxStringClientData(propertyInfo));
	m_grid->Append(property);

	property = new wxFloatProperty(displayName + " Z", wxName + ".z", val.z);
	property->SetClientObject(new wxStringClientData(propertyInfo));
	m_grid->Append(property);

	return true;
}

bool rePropertyReader::Color(const rString& name, rColor& color) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(wxName);
	wxColor wxc(color.red, color.green, color.blue);
	wxString propertyInfo = wxString::Format("color:%s", name.c_str());

	wxColourProperty* property = new wxColourProperty(displayName, wxName, wxc);
	property->SetClientObject(new wxStringClientData(propertyInfo));

	m_grid->Append(property);

	return true;
}

bool rePropertyReader::Category(const rString& name) {
	wxString wxName = name.c_str();
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxPropertyCategory(displayName, wxName));

	return true;
}

wxString rePropertyReader::DisplayName(const wxString& name){
	wxString wxstr;
	wxStringOutputStream buffer(&wxstr);
	wxTextOutputStream str(buffer);

	for (size_t i = 0; i < name.length(); i++){
		wxUniChar c = name[i];
		if (i == 0) {
			str.PutChar(std::toupper(c));
		}
		else if (std::isupper(name[i])){
			str.PutChar(' ').PutChar(c);
		}
		else{
			str.PutChar(c);
		}
	}

	return wxstr;
}

////rePropertyWriter

rePropertyWriter::rePropertyWriter(){
	m_propertySet = false;
}

bool rePropertyWriter::PropertySet() const{
	return m_propertySet;
}

void rePropertyWriter::SetProperty(const wxString& propertyName, const wxAny& anyVal){
	m_propertyName = propertyName.c_str().AsChar();
	m_value = anyVal;
	m_propertySet = true;
}

void rePropertyWriter::Write(rActor3* actor){
	actor->Load(this);
}

bool rePropertyWriter::Boolean(const rString& name, bool& val){
	return DoGetValue<bool>(name, val);
}

bool rePropertyWriter::Int(const rString& name, int& val){
	return DoGetValue<int>(name, val);
}

bool rePropertyWriter::Float(const rString& name, float& val){
	return DoGetValue<float>(name, val);
}

bool rePropertyWriter::String(const rString& name, rString& val){
	return DoGetValue<rString>(name, val);
}

bool rePropertyWriter::Vector3(const rString& name, rVector3& val){
	return DoGetValue<rVector3>(name, val);
}

bool rePropertyWriter::Color(const rString& name, rColor& val){
	return DoGetValue<rColor>(name, val);
}

//rePropertyGetter
rePropertyGetter::rePropertyGetter(){
	m_propertySet = false;
}

bool rePropertyGetter::Boolean(const rString& name, bool& val){
	DoSetValue<bool>(name, val);

	return m_propertySet;
}

bool rePropertyGetter::Int(const rString& name, int& val){
	DoSetValue<int>(name, val);

	return m_propertySet;
}

bool rePropertyGetter::Float(const rString& name, float& val){
	DoSetValue<float>(name, val);

	return m_propertySet;
}

bool rePropertyGetter::String(const rString& name, rString& val){
	DoSetValue<rString>(name, val);

	return m_propertySet;
}

bool rePropertyGetter::Vector3(const rString& name, rVector3& val){
	DoSetValue<rVector3>(name, val);

	return m_propertySet;
}

bool rePropertyGetter::Color(const rString& name, rColor& val){
	DoSetValue<rColor>(name, val);

	return m_propertySet;
}

const wxAny& rePropertyGetter::GetValue() const{
	return m_value;
}

void rePropertyGetter::GetProperty(const wxString& propertyName, rActor3* actor){
	m_propertyName = propertyName.c_str().AsChar();

	actor->Save(this);
}

bool rePropertyGetter::PropertySet() const{
	return m_propertySet;
}