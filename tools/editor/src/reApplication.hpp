#ifndef RE_APPLICATION_HPP
#define RE_APPLICATION_HPP

#include "wx/wx.h"

#include "rwxComponent.hpp"

#include "reMainFrame.hpp"

class reApplication : public wxApp{
public:
	virtual bool OnInit();

private:
	rwxComponent* m_rwxComponent;
};

#endif