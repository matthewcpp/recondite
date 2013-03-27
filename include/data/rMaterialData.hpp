#ifndef R_MATERIAL_DATA_HPP
#define R_MATERIAL_DATA_HPP

#include <map>
#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "xml/rXMLDocument.hpp"

struct rMaterialParameterData{
	rMaterialParameterType type;
	rString value;
};

typedef std::map<rString, rMaterialParameterData> rMaterialParameterDataMap;
typedef rMaterialParameterDataMap::const_iterator rMaterialParameterDataConstItr;

class rMaterialData{
public:
	rMaterialData();
	rMaterialData(const rString& path);
	rMaterialData(std::istream& stream);
	rMaterialData(const rString& shaderName, const rString& shaderPath, const rMaterialParameterDataMap& parameters);
	~rMaterialData();
	
	rContentError LoadFromPath(const rString& path);
	rContentError LoadFromStream(std::istream& stream);
	
	rContentError WriteToPath(const rString& path);
	rContentError WriteToStream(std::ostream& stream);
	
	void SetMaterialData(const rString& shaderName, const rString& shaderPath, const rMaterialParameterDataMap& parameters);
	
	void Clear();
	
public:	
	rString GetPath() const;
	void SetPath(const rString& path);
	
	rString GetShaderName() const;
	rString GetShaderPath() const;
	
	size_t GetParameterCount() const;
	bool GetParameterData(const rString& name, rMaterialParameterData& data) const;
	void GetParameterNames(rArrayString& names) const;
	void GetParameterNamesForType(rArrayString& names, rMaterialParameterType type) const;
	
	rContentError GetError() const;
	
private :

	rContentError LoadShaderData(const rXMLDocument& xml);
	rContentError LoadParameters(const rXMLDocument& xml);
	
	static rMaterialParameterType GetParameterType(const rString& type);
	static rString GetParamterTypeName(rMaterialParameterType type);
	
private:
	rString m_shaderName;
	rString m_shaderPath;
	
	rMaterialParameterDataMap m_parameters;
	
	rString m_path;
	rContentError m_error;
};

#endif
