#ifndef RUI_STYLE_HPP
#define RUI_STYLE_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rColor.hpp"

#include "rFont.hpp"
#include "rTexture2D.hpp"

union ruiStyleProperty{
	int m_int;
	float m_float;
	unsigned char m_color[4];
	rTexture2D* m_texture;
	rFont* m_font;
};

typedef std::map<rString, ruiStyleProperty> ruiStylePropertyMap;

class ruiStyle{
public:
	bool GetFont(const rString& name, rFont** font) const;
	void SetFont(const rString& name, rFont* font);

	bool GetTexture(const rString& name, rTexture2D** texture) const;
	void SetTexture(const rString& name, rTexture2D* texture);

	bool GetInt(const rString& name, int& i) const;
	void SetInt(const rString& name, int i);

	bool GetFloat(const rString& name, float& f) const;
	void SetFloat(const rString& name, float f);

	bool GetColor(const rString& name, rColor& color) const;
	void SetColor(const rString& name, const rColor& color);

	void Extend(const ruiStyle& style);

private:
	ruiStylePropertyMap m_properties;
};

#endif