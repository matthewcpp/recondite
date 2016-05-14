#ifndef RUI_MANAGER_HPP
#define RUI_MANAGER_HPP

#include <map>

#include "rBuild.hpp"

#include "rInput.hpp"
#include "rEngine.hpp"

#include "rViewport.hpp"

#include "ui/ruiOverlay.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiMenuManager.hpp"
#include "ui/ruiController.hpp"

class ruiMenu;
class ruiOverlay;

class RECONDITE_API ruiIManager {
public:
	virtual ruiOverlay* CreateOverlay(rViewport* viewport) = 0;
	virtual ruiOverlay* LoadOverlay(const rString& filePath, rViewport* viewport) = 0;
	virtual ruiOverlay* GetOverlay(rViewport* viewport) const = 0;

	typedef ruiController*(*ControllerCreateFunction)(const rString& className, rEngine*, ruiOverlay*);
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

	virtual ruiOverlay* CreateOverlay(rViewport* viewport);
	virtual ruiOverlay* LoadOverlay(const rString& filePath, rViewport* viewport);
	virtual ruiOverlay* GetOverlay(rViewport* viewport) const;
	

	virtual bool RegisterControllerClass(const rString& name, ControllerCreateFunction createFunc, ControllerDeleteFunction deleteFunc);
	virtual void UnregisterControllerClass(const rString& name);
	virtual ruiController* CreateController(const rString& name, ruiOverlay* overlay);

private:
	struct Impl;
	Impl* _impl;
};

#endif
