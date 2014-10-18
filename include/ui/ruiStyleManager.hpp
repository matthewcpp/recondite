#ifndef RUI_STYLEMANAGER_HPP
#define RUI_STYLEMANAGER_HPP

#include <map>
#include <istream>

#include "rBuild.hpp"
#include "rString.hpp"

#include "ruiStyle.hpp"
#include "ui/ruiStylesheetLoader.hpp"

class RECONDITE_API ruiStyleManager{
public:
	ruiStyleManager();
	~ruiStyleManager();

	ruiStyle* CreateStyle(const rString& selector);
	ruiStyle* GetStyle(const rString& selector) const;

	size_t StyleCount() const;
	void Clear();

	bool ParseStylesheet(rIStream& stream);

private:
	ruiStyleMap m_styles;
};

#endif