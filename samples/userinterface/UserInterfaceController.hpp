#pragma once

#include "rEngine.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiController.hpp"

class UserInterfaceController : public ruiController{
public:
	UserInterfaceController(const rString& name, rEngine* engine, ruiDocument* document);
	virtual void OnDocumentLoaded();

private:
	void OnRotateCheckboxClick(rEvent& event);
	void OnRotationSpeedSliderChange(rEvent& event);

private:
	rEngine* _engine;
	ruiDocument* _document;

	uint32_t _rotateHandle;
	float _rotationSpeed;
};