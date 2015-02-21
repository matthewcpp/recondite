#ifndef RE_COMPONENT_HPP
#define RE_COMPONENT_HPP

#include <memory>

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/cmdproc.h>

#include "reSelectionManager.hpp"
#include "reProject.hpp"

class reComponent : public rwxComponent{
public:
	reComponent();
	reSelectionManager* GetSelection();
	reProject* GetProject();

	bool SubmitCommand(wxCommand* command);
	void InitCommandProcessor(wxMenu* editMenu);

private:
	std::unique_ptr<reSelectionManager> m_selectionManager;
	std::unique_ptr<reProject> m_project;

	wxCommandProcessor m_commandProcessor;
};

#endif