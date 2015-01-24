#ifndef RE_APPLICATION_HPP
#define RE_APPLICATION_HPP

#include "wx/wx.h"

#include "reMainFrame.hpp"

class reApplication : public wxApp{
public:
	virtual bool OnInit();
};

#endif