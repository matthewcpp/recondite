#ifndef RUI_MENU_HPP
#define RUI_MENU_HPP

#include <vector>

#include "rBuild.hpp"
#include "rString.hpp"

#include "rEngine.hpp"

#include "ui/ruiStyle.hpp"

class RECONDITE_API ruiMenuItem{
public:
	ruiMenuItem(int id, const rString& label);

	rString Label() const;
public:
	int m_id;
	rString m_label;
	bool m_checked;
	unsigned short m_radioId;
};

class RECONDITE_API ruiMenu{
public:
	ruiMenu();
	~ruiMenu();

public:
	ruiMenuItem* AppendItem(int id, const rString& label);
	ruiMenuItem* GetItem(size_t index) const;
	void DeleteItem(size_t index);

	void Draw(const rRect& bounding, rEngine& engine);
	void Update(rEngine& engine);

	void Clear();

private:
	typedef std::vector<ruiMenuItem*> ruiMenuItemArray;

private:
	ruiMenuItemArray m_menuItems;
};

#endif