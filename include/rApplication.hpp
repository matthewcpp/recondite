#ifndef R_APPLICATION_HPP
#define R_APPLICATION_HPP

#include "rEngine.hpp"

class rApplication{
public:
	virtual unsigned long GetTimeMiliseconds() const = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

public:
	rApplication();
	virtual ~rApplication();

	bool IsRunning() const;

	virtual void Tick();

	unsigned int GetTargetFPS() const;
	void SetTargetFPS(unsigned int targetFPS);

protected:
	bool m_isRunning;
	unsigned int m_targetFPS;

	rEngine m_engine;

	unsigned int m_frameCount;
};

#endif