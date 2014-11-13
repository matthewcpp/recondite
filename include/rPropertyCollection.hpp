#ifndef R_PROPERTYCOLLECTION_HPP
#define R_PROPERTYCOLLECTION_HPP

#include <map>

#include "rBuild.hpp"
#include "rTypes.hpp"

#include "rString.hpp"
#include "rColor.hpp"
#include "rFont.hpp"
#include "rTexture2D.hpp"

enum rPropertyType{
	rPROPERTY_TYPE_BOOL,
	rPROPERTY_TYPE_INT,
	rPROPERTY_TYPE_FLOAT,
	rPROPERTY_TYPE_STRING,
	rPROPERTY_TYPE_COLOR,
	rPROPERTY_TYPE_FONT,
	rPROPERTY_TYPE_TEXTURE,
	rPROPERTY_TYPE_UNKNOWN
};

union rPropertyValue{
	bool boolVal;
	int intVal;
	float floatVal;
	rString* stringVal;
	rColor* colorVal;
	rFont* fontVal;
	rTexture2D* textureVal;
};

struct rProperty{
	rProperty(bool b);
	rProperty(int i);
	rProperty(float f);
	rProperty(const rString& s);
	rProperty(const rColor& c);
	rProperty(rFont* f);
	rProperty(rTexture2D* t);

	~rProperty();

	rPropertyType type;
	rPropertyValue value;
};

class RECONDITE_API rPropertyCollection{
public:
	~rPropertyCollection();

	void SetBool(const rString& key, bool val);
	bool GetBool(const rString& key, bool& val) const;

	void SetInt(const rString& key, int val);
	bool GetInt(const rString& key, int& val) const;

	void SetFloat(const rString& key, float val);
	bool GetFloat(const rString& key, float& val) const;

	void SetString(const rString& key, const rString& val);
	bool GetString(const rString& key, rString& val);

	void SetColor(const rString& key, const rColor& val);
	bool GetColor(const rString& key, rColor& val) const;

	void SetFont(const rString& key, rFont* val);
	bool GetFont(const rString& key, rFont*& font) const;

	void SetTexture(const rString& key, rTexture2D* val);
	bool GetTexture(const rString& key, rTexture2D*& texture) const;

	void DeleteProperty(const rString& key);
	size_t NumProperties() const;

	rPropertyType GetType(const rString& key) const;
	void GetKeys(rArrayString& keys) const;

	void Clear();

protected:
	typedef std::map<rString, rProperty*> rPropertyMap;

protected:
	rPropertyMap m_properties;
};

#endif