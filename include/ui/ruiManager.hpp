#ifndef RUI_MANAGER_HPP
#define RUI_MANAGER_HPP

#include <map>

#include "rBuild.hpp"

#include "rInput.hpp"
#include "rEngine.hpp"

#include "rViewport.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiMenuManager.hpp"
#include "ui/ruiController.hpp"

class ruiMenu;
class ruiDocument;

class RECONDITE_API ruiIManager {
public:
	virtual ruiDocument* CreateUiDocument(rViewport* viewport) = 0;
	virtual ruiDocument* LoadUiDocument(const rString& filePath, rViewport* viewport) = 0;
	virtual ruiDocument* GetUiDocument(rViewport* viewport) const = 0;

	typedef ruiController*(*ControllerCreateFunction)(const rString& className, rEngine*, ruiDocument*);
	typedef void(*ControllerDeleteFunction)(ruiController* controller);

	virtual bool RegisterControllerClass(const rString& name, ControllerCreateFunction createFunc, ControllerDeleteFunction deleteFunc) = 0;
	virtual void UnregisterControllerClass(const rString& name) = 0;
};

class RECONDITE_API ruiManager : public ruiIManager {
public:
	ruiManager(rEngine* engine);
	~ruiManager();
	
public:

	virtual bool InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position);
	virtual bool InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction);
	virtual bool InsertMouseMotionEvent(const rPoint& point);

	virtual bool InsertTouchEvent(int id, const rPoint& position, rTouchType type);
	virtual bool InsertKeyEvent(rKey key, rKeyState state);
	
	void Update();
	void Draw(rViewport* viewport);

	void Clear();

	virtual ruiDocument* CreateUiDocument(rViewport* viewport);
	virtual ruiDocument* LoadUiDocument(const rString& filePath, rViewport* viewport);
	virtual ruiDocument* GetUiDocument(rViewport* viewport) const;
	

	virtual bool RegisterControllerClass(const rString& name, ControllerCreateFunction createFunc, ControllerDeleteFunction deleteFunc);
	virtual void UnregisterControllerClass(const rString& name);
	virtual ruiController* CreateController(const rString& name, ruiDocument* document);

private:
	struct Impl;
	Impl* _impl;
};

#endif
