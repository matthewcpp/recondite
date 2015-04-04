#ifndef RE_COMPONENT_HPP
#define RE_COMPONENT_HPP

#include <memory>
#include <set>

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/cmdproc.h>

#include "reSelectionManager.hpp"
#include "reProject.hpp"

#include "primitive/rPrimitiveGrid.hpp"

class reComponent : public rwxComponent{
public:
	reComponent();
	reSelectionManager* GetSelection();
	reProject* GetProject();

	bool Init(wxGLCanvas* canvas) override;

	bool SubmitCommand(wxCommand* command);
	void InitCommandProcessor(wxMenu* editMenu);

	virtual bool SaveScene(const rString& path) override;
	virtual void ClearScene() override;

	void AddReservedActor(rActor3* actor);
	bool IsReservedActor(const rString& id);

private:
	void OnSceneLoad(rEvent& event);

private:
	std::unique_ptr<reSelectionManager> m_selectionManager;
	std::unique_ptr<reProject> m_project;
	std::set<rString> m_reservedActors;

	wxCommandProcessor m_commandProcessor;
};

#endif