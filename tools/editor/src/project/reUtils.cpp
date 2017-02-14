#include "reUtils.hpp"

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/ffile.h>

namespace reUtils {
	bool RecursiveCopy(const wxString& src, const wxString& dest) {
		wxDir srcDir(src);

		wxFileName srcFile, destFile;
		srcFile.SetPath(src);
		destFile.SetPath(dest);

		if (!destFile.Exists()) {
			destFile.Mkdir();
		}
		
		wxString currentFile;
		if (srcDir.IsOpened()) {
			bool cont = srcDir.GetFirst(&currentFile, wxEmptyString, wxDIR_FILES | wxDIR_DIRS);

			while (cont) {
				wxString srcFileName(srcFile.GetPathWithSep() + currentFile);
				wxString destFileName(destFile.GetPathWithSep() + currentFile);

				if (wxDirExists(srcFileName)) {
					RecursiveCopy(srcFileName, destFileName);
				}
				else {
					wxCopyFile(srcFileName, destFileName);
				}

				cont = srcDir.GetNext(&currentFile);
			}

			return true;
		}
		else {
			return false;
		}
	}


	bool CopyAndReplaceInFile(const wxString& src, const wxString& dest, const wxString& search, const wxString& replace) {
		wxArrayString searchArray, replaceArray;
		searchArray.push_back(search);
		replaceArray.push_back(replace);

		return CopyAndReplaceInFile(src, dest, searchArray, replaceArray);
	}

	bool CopyAndReplaceInFile(const wxString& src, const wxString& dest, const wxArrayString& search, const wxArrayString replace) {
		wxASSERT(wxFileExists(src));
		wxASSERT(search.size() == replace.size());

		wxFFile srcFile(src, "r");

		wxString fileContents;
		srcFile.ReadAll(&fileContents);
		srcFile.Close();

		for (size_t i = 0; i < search.size(); i++) {
			fileContents.Replace(search[i], replace[i]);
		}

		wxFFile destFile(dest, "w");
		destFile.Write(fileContents);

		return true;
	}

	bool ReplaceInFile(const wxString& src, const wxString& search, const wxString& replace) {
		wxArrayString searchArray, replaceArray;
		searchArray.push_back(search);
		replaceArray.push_back(replace);

		return ReplaceInFile(src, searchArray, replaceArray);
	}

	bool ReplaceInFile(const wxString& src, const wxArrayString& search, const wxArrayString replace) {
		wxASSERT(wxFileExists(src));
		wxASSERT(search.size() == replace.size());

		wxFFile srcFile(src, "r");

		wxString fileContents;
		srcFile.ReadAll(&fileContents);
		srcFile.Close();

		for (size_t i = 0; i < search.size(); i++) {
			fileContents.Replace(search[i], replace[i]);
		}

		srcFile.Open(src, "w");
		srcFile.Write(fileContents);

		return true;
	}
}