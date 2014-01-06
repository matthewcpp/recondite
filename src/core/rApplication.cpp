#include "rApplication.hpp"

rApplication::rApplication(){
	m_isRunning = false;
	m_frameCount = 0;
}

rApplication::~rApplication(){
}

bool rApplication::IsRunning() const{
	return m_isRunning;
}

void rApplication::Tick(){
	unsigned long time = GetTimeMiliseconds();

	unsigned long delta = time - m_engine.time.LastUpdateTime();
	unsigned int ms = 1000 / m_targetFPS;

	if (delta >= ms){
		m_engine.time.Update(time);
		Update();
		Draw();
	}
}

unsigned int rApplication::GetTargetFPS() const{
	return m_targetFPS;
}

void rApplication::SetTargetFPS(unsigned int targetFPS){
	m_targetFPS = targetFPS;
}