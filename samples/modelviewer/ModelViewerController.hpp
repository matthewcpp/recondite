#pragma once

#include "ModelViewerSettings.hpp"

#include "rEngine.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiController.hpp"

class ModelViewerController : public ruiController {
public:
	ModelViewerController(ModelViewerSettings* settings, const rString& name, rEngine* engine, ruiDocument* document);
	virtual void OnDocumentLoaded();

private:
	void OnMouseEnter(rEvent& event);
	void OnMouseLeave(rEvent& event);

	void OnShowSkeletonClick(rEvent& event);
	void OnShowBoneNamesClick(rEvent& event);

	void OnAnimationPickerChange(rEvent& event);
	void OnAnimationPlayButtonClick(rEvent& event);
	void OnAnimationPauseButtonClick(rEvent& event);
	void OnAnimationStopButtonClick(rEvent& event);

	void SetColorForWidgetEvent(rEvent& event, const rColor& color);

	void CameraDebug();

private:
	ModelViewerSettings* _settings;
	rEngine* _engine;
	ruiDocument* _document;
};