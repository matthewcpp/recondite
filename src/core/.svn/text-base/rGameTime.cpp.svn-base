#include "rGameTime.hpp"

rGameTime::rGameTime(){
	Init();
}

void rGameTime::Start(unsigned long seedTime){
	Init();

	m_lastUpdateTime = seedTime;
	
}

void rGameTime::Update(unsigned long currentTime){
	m_timeDeltaMilliseconds = currentTime - m_lastUpdateTime;

	m_gameTime += m_timeDeltaMilliseconds;
	m_timeDeltaSeconds = float(m_timeDeltaMilliseconds) / 1000.0f;

	m_lastUpdateTime = currentTime;
}

void rGameTime::Init(){
	m_gameTime = 0;
	m_timeDeltaMilliseconds = 0;
	m_lastUpdateTime = 0;
	m_timeDeltaSeconds = 0.0f;
}