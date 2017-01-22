#ifndef RE_COMPONENT_HPP
#define RE_COMPONENT_HPP

#include <memory>
#include <set>

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/cmdproc.h>
#include <wx/fileconf.h>

#include "reSelectionManager.hpp"
#include "reProject.hpp"
#include "reProjectResourceManager.hpp"

class rwxGLCanvas;

class reViewportManager {
public:
	virtual void UpdateAllViewports(bool force = false) = 0;
	virtual void MaximizeViewport(int id) = 0;
	virtual void RestoreViewports() = 0;
	virtual void HoverCanvas(rwxGLCanvas* canvas) = 0;
};

enum reComponentEvent{
	reCommandProcessed = 7000,

	reExternalPropertyChange
};

enum class reViewOrientation {
	Front,
	Back,
	Left,
	Right,
	Top,
	Bottom,
	User
};

class reComponent : public rwxComponent{
public:
	reComponent();

	reSelectionManager* SelectionManager();
	reProject* GetProject();

	virtual bool Init();

	bool SubmitCommand(wxCommand* command);
	bool UndoCommand();
	bool RedoCommand();
	void InitCommandProcessor(wxMenu* editMenu);

	virtual void AfterSceneRendered(rViewport* viewport) override;

	void SetViewportManager(reViewportManager* viewportManager);
	reViewportManager* GetViewportManager();

	wxConfigBase* GetConfig();

private:
	std::unique_ptr<reSelectionManager> m_selectionManager;
	std::unique_ptr<reProject> m_project;
	std::unique_ptr<reProjectResourceManager> m_resourceManager;
	std::unique_ptr<wxFileConfig> m_config;

	reViewportManager* m_viewportManager;

	wxCommandProcessor m_commandProcessor;
};

#endif