#ifndef RUI_MENU_HPP
#define RUI_MENU_HPP

#include <vector>

#include "rBuild.hpp"
#include "rString.hpp"

class RECONDITE_API ruiMenuItem{
public:
	ruiMenuItem(int id, const rString& label);

	rString Label() const;
public:
	int m_id;
	rString m_label;
};

class RECONDITE_API ruiMenu{
public:
	ruiMenu();
	~ruiMenu();

public:
	ruiMenuItem* AppendItem(int id, const rString& label);
	ruiMenuItem* GetItem(size_t index) const;
	size_t NumItems() const;
	void DeleteItem(size_t index);

	void Clear();

private:
	typedef std::vector<ruiMenuItem*> ruiMenuItemArray;

private:
	ruiMenuItemArray m_menuItems;
};

#endif