#ifndef RUI_DEMOCONTROLLER_HPP
#define RUI_DEMOCONTROLLER_HPP

#include <sstream>
#include <map>

#include "ui/ruiPicker.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiOverlayManager.hpp"
#include "ui/ruiText.hpp"
#include "ui/ruiTextBox.hpp"

#include "rContentManager.hpp"
#include "data/rGeometryData.hpp"
#include "data/rGeometryDataFile.hpp"

#include "rDemoCamera.hpp"

#include "rEngine.hpp"
#include "rPawn.hpp"

#include "rLog.hpp"

typedef std::map<rString, rImmediateBuffer*> rImmediateBufferMap;

class ruiDemoController{
public:
	ruiDemoController(rContentManager* contentManager, rPawn* pawn, rDemoCamera* camera);
	~ruiDemoController();

	virtual void Init(ruiOverlay* overlay);

	void OnUpdate(rEngine& engine);
	void OnDraw(rEngine& engine);

	void OnModelChange(ruiWidget* widget);
	void OnAnimationChange(ruiWidget* widget);

	void OnAnimationPlay(ruiWidget* widget);
	void OnAnimationPause(ruiWidget* widget);
	void OnAnimationStop(ruiWidget* widget);

private:
	void SetActiveModel(const rString& name);

	void SetupImmediateBuffer(const rString name);
	void RenderAnimated(rEngine& engine);
	

private:
	rContentManager* m_contentManager;

	ruiPicker* m_modelPicker;
	ruiPicker* m_animationPicker;

	ruiText* m_animationTime;
	ruiSlider* m_progressSlider;

	rPawn* m_pawn;
	rDemoCamera* m_camera;

	//temp
	rGeometryData m_geometryData;
	rImmediateBufferMap m_buffers;
};

#endif
