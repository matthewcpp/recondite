#pragma once

#include "rEngine.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiController.hpp"

class ModelViewerController : public ruiController {
public:
	ModelViewerController(const rString& name, rEngine* engine, ruiDocument* document);
	virtual void OnDocumentLoaded();

private:
	rEngine* _engine;
	ruiDocument* _document;
};