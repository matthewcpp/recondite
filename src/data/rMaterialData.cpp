#include "data/rMaterialData.hpp"

rMaterialParameterData::rMaterialParameterData(rMaterialParameterType t, const rString& n, const rString& v, const rString& p){
	Set(t,n,v,p);
}

rMaterialParameterData::rMaterialParameterData(const rMaterialParameterData& data){
	Set(data.type, data.name, data.value, data.path);
}

void rMaterialParameterData::Set(rMaterialParameterType t, const rString& n, const rString& v, const rString& p){
	type = t;
	name = n;
	value = v;
	path = p;
}

rMaterialData::rMaterialData(){
	Clear();
}

rMaterialData::rMaterialData(const rString& path){
	LoadFromPath(path);
}

rMaterialData::rMaterialData(rIStream& stream){
	LoadFromStream(stream);
}

rMaterialData::rMaterialData(const rString& shaderName, const rString& shaderPath, const rMaterialParameterDataMap& parameters){
	SetMaterialData(shaderName, shaderPath, parameters);
}

rMaterialData::~rMaterialData(){}

rContentError rMaterialData::LoadFromPath(const rString& path){
	m_error = rCONTENT_ERROR_NONE;
	
	rIFileStream stream(path.c_str());
	
	if (!stream)
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
	else
		m_error = LoadFromStream(stream);
	
	SetPath(path);
	stream.Close();
	
	return m_error;
}

rContentError rMaterialData::LoadShaderData(const rXMLDocument& xml){
	rXMLElement* shaderNode = xml.GetRoot()->GetFirstChildNamed("shader");
	
	if (!shaderNode)
		return rCONTENT_ERROR_PARSE_ERROR;
	
	rXMLElement* shaderNameNode = shaderNode->GetFirstChildNamed("name");
	
	if (!shaderNameNode)
		return rCONTENT_ERROR_PARSE_ERROR;
	
	m_shaderName = shaderNameNode->Text();
	
	rXMLElement* shaderPathNode = shaderNode->GetFirstChildNamed("path");
	
	if (!shaderPathNode)
		return rCONTENT_ERROR_PARSE_ERROR;
	
	m_shaderPath = shaderPathNode->Text();
	
	return rCONTENT_ERROR_NONE;
}

rMaterialParameterType rMaterialData::GetParameterType(const rString& type){
	if (type == "texture2D")
		return rMATERIAL_PARAMETER_TEXTURE2D;
	else if (type == "color")
		return rMATERIAL_PARAMETER_COLOR;
	else
		return rMATERIAL_PARAMETER_UNKNOWN;
}

rString rMaterialData::GetParamterTypeName(rMaterialParameterType type){
	switch(type){
		case rMATERIAL_PARAMETER_TEXTURE2D:
			return "texture2D";
		case rMATERIAL_PARAMETER_COLOR:
			return "color";
		default:
			return "unknown";
	}
}

rContentError rMaterialData::LoadParameters(const rXMLDocument& xml){
	rXMLElementArray elements;
	xml.FindElements("parameter", elements);
	
	rString paramName, type;
	rMaterialParameterData parameter;
	rXMLElement* value, *name, *path;
	
	for (size_t i = 0; i < elements.size(); i++){
		if (elements[i]->GetAttribute<rString>("type", type))
			parameter.type = GetParameterType(type);
		else
			return rCONTENT_ERROR_PARSE_ERROR;
		
		name = elements[i]->GetFirstChildNamed("name");
		
		if (!name)
			return rCONTENT_ERROR_PARSE_ERROR;
		
		paramName = name->Text();
		
		value = elements[i]->GetFirstChildNamed("value");
		
		if (!value)
			return rCONTENT_ERROR_PARSE_ERROR;
		
		parameter.value = value->Text();
		
		path = elements[i]->GetFirstChildNamed("path");
		
		if (!path)
			return rCONTENT_ERROR_PARSE_ERROR;
			
		parameter.path = path->Text();
		
		m_parameters[paramName] = parameter;
	}
	
	
	return rCONTENT_ERROR_NONE;
}

rContentError rMaterialData::LoadFromStream(rIStream& stream){
	Clear();
	
	if (!stream){
		m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
		return m_error;
	}

	rXMLDocument document;
	rXMLReaderError xmlError = document.LoadFromStream(stream);
	
	if (!xmlError){
		LoadShaderData(document);
		LoadParameters(document);
	}
	else
		m_error = rCONTENT_ERROR_PARSE_ERROR;
		
	
	
	return m_error;
}

rContentError rMaterialData::WriteToPath(const rString& path){
	std::ofstream stream(path.c_str(), std::ios::binary);
	
	if (!stream)
		m_error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
	else
		m_error = WriteToStream(stream);
	
	stream.close();
	
	return m_error;
}

rContentError rMaterialData::WriteToStream(std::ostream& stream){
	rContentError error = rCONTENT_ERROR_NONE;
	
	rXMLDocument xml;
	rXMLElement* root = xml.CreateRoot("material");
	
	rXMLElement* shaderNode = root->CreateChild("shader");
	shaderNode->CreateChild("name", m_shaderName);
	shaderNode->CreateChild("path", m_shaderPath);
	
	rXMLElement* parameterNode = root->CreateChild("parameters");
	
	for (rMaterialParameterDataConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it){
		rXMLElement* paramNode = parameterNode->CreateChild("parameter");
		paramNode->AddAttribute("type", GetParamterTypeName(it->second.type));
		paramNode->CreateChild("name", it->first);
		paramNode->CreateChild("value", it->second.value);
		paramNode->CreateChild("path", it->second.path);
	}

	xml.WriteToStream(stream);
	
	return error;
}

void rMaterialData::SetMaterialData(const rString& shaderName, const rString& shaderPath, const rMaterialParameterDataMap& parameters){
	Clear();
	
	m_shaderName = shaderName;
	m_shaderPath = shaderPath;
	m_parameters = parameters;
}

void rMaterialData::Clear(){
	m_shaderName.clear();
	m_shaderPath.clear();
	m_parameters.clear();
	
	m_path.clear();
	m_error = rCONTENT_ERROR_NONE;
}

rString rMaterialData::GetPath() const{
	return m_path;
}

void rMaterialData::SetPath(const rString& path){
	m_path = path;
}

void rMaterialData::SetShader(const rString& shaderName, const rString& shaderPath){
	m_shaderName = shaderName;
	m_shaderPath = shaderPath;
}

rString rMaterialData::GetShaderName() const{
	return m_shaderName;
}

void rMaterialData::SetParameter(rMaterialParameterType type, const rString& name, const rString& value){
	SetParameter(type, name, value, "");
}

void rMaterialData::SetParameter(rMaterialParameterType type, const rString& name, const rString& value, const rString& path){
	m_parameters[name] = rMaterialParameterData (type, name, value, path);
}

rString rMaterialData::GetShaderPath() const{
	return m_shaderPath;
}

size_t rMaterialData::GetParameterCount() const{
	return m_parameters.size();
}

bool rMaterialData::GetParameterData(const rString& name, rMaterialParameterData& data) const{
	rMaterialParameterDataConstItr result = m_parameters.find(name);
	
	if (result != m_parameters.end()){
		data = result->second;
		return true;
	}
	else
		return false;
}

void rMaterialData::GetParameterNames(rArrayString& names) const{
	names.clear();
	
	for (rMaterialParameterDataConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it)
		names.push_back(it->first);
}

void rMaterialData::GetParameterNamesForType(rArrayString& names, rMaterialParameterType type) const{
	names.clear();
	
	for (rMaterialParameterDataConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it){
		if (it->second.type == type)
			names.push_back(it->first);
	}
}


rContentError rMaterialData::GetError() const{
	return m_error;
}
