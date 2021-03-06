#pragma once

#include "SkeletonGeometry.hpp"

#include "rEngine.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiController.hpp"

class ModelViewerController : public ruiController {
public:
	ModelViewerController(SkeletonGeometry* skeletonGeometry, const rString& name, rEngine* engine, ruiDocument* document);
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
	void OnAnimationLoopCheckboxClick(rEvent& event);
	void OnAnimationProgressDrag(rEvent& event);
	void OnAnimationSpeedKey(rEvent& event);

	void SetColorForWidgetEvent(rEvent& event, const rColor& color);
	void OnUpdate();

	void CameraDebug();

private:
	SkeletonGeometry* _skeletonGeometry;
	rEngine* _engine;
	ruiDocument* _document;
};