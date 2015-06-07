#ifndef RUI_STYLE_HPP
#define RUI_STYLE_HPP

#include <map>

#include "rBuild.hpp"
#include "rColor.hpp"

#include "rPropertyCollection.hpp"


class RECONDITE_API ruiStyle : public rPropertyCollection {
public:
	ruiStyle();

	void SetBool(const rString& key, bool val);
	void SetFont(const rString& key, rFont* font);
	void SetTexture(const rString& key, rTexture* texture);
	void SetInt(const rString& key, int i);
	void SetFloat(const rString& key, float f);
	void SetColor(const rString& key, const rColor& color);

	void Extend(const ruiStyle& style);

	bool HasChanged() const;
	void MarkChanged();
	void ClearChanged();

private:
	bool m_changed;
};

typedef std::map<rString, ruiStyle*> ruiStyleMap;

#endif