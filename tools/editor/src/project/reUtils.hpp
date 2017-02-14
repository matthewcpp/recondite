#pragma once

#include <wx/wx.h>

namespace reUtils {
	bool RecursiveCopy(const wxString& src, const wxString& dest);
	
	bool CopyAndReplaceInFile(const wxString& src, const wxString& dest, const wxString& search, const wxString& replace);
	bool CopyAndReplaceInFile(const wxString& src, const wxString& dest, const wxArrayString& search, const wxArrayString replace);

	bool ReplaceInFile(const wxString& src, const wxString& search, const wxString& replace);
	bool ReplaceInFile(const wxString& src, const wxArrayString& search, const wxArrayString replace);
}