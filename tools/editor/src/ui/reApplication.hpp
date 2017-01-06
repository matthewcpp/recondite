#ifndef RE_APPLICATION_HPP
#define RE_APPLICATION_HPP

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h> 

#include "project/reComponent.hpp"
#include "project/reProject.hpp"

#include "reMainFrame.hpp"

class reApplication : public wxApp{
public:
	virtual bool OnInit();
	virtual int OnExit();

private:
	void SetupPaths();

private:
	reComponent* m_reComponent;
};

#endif