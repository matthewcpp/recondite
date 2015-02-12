#ifndef RE_APPLICATION_HPP
#define RE_APPLICATION_HPP

#include "wx/wx.h"

#include "rwxComponent.hpp"

#include "project/reProject.hpp"

#include "reMainFrame.hpp"

class reApplication : public wxApp{
public:
	virtual bool OnInit();
	virtual int OnExit();

private:
	rwxComponent* m_rwxComponent;
	reProject* m_project;
};

#endif