#ifndef R_APPLICATION_HPP
#define R_APPLICATION_HPP

#include "rEngine.hpp"
#include "rModule.hpp"
#include "rGraphicsDevice.hpp"
#include "rInputManager.hpp"

class rApplication{
public:
	virtual unsigned long GetTimeMiliseconds() const = 0;
	virtual void Update();
	virtual void Draw();

public:
	rApplication(rModule* module);
	virtual ~rApplication();

	bool IsRunning() const;

	virtual void Tick();

	unsigned int GetTargetFPS() const;
	void SetTargetFPS(unsigned int targetFPS);

protected:
	void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input);

protected:
	bool m_isRunning;
	unsigned int m_targetFPS;
	unsigned int m_frameCount;

	rEngine m_engine;
	rModule* m_module;

	rGraphicsDevice* m_graphicsDevice;
	ruiLayoutManager* m_layoutManager;
};

#endif
