#pragma once

#include "wx/wx.h"

class reUIController {
public:

	virtual bool ActivateLevel(const wxString& levelName) = 0;

};