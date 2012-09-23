#ifndef R_GAME_TIME_HPP
#define R_GAME_TIME_HPP

class rGameTime{
public:
	rGameTime();

	void Start(unsigned long seedTime);
	void Update(unsigned long currentTime);

	inline unsigned long GameTime() const;
	inline float TimeDeltaSeconds() const;
	inline unsigned long TimeDeltaMilliseconds() const;

private:

	void Init();

	unsigned long m_gameTime;
	unsigned long m_lastUpdateTime;

	float m_timeDeltaSeconds;
	unsigned long m_timeDeltaMilliseconds;
};

unsigned long rGameTime::GameTime() const{
	return m_gameTime;
}

float rGameTime::TimeDeltaSeconds() const{
	return m_timeDeltaSeconds;
}

unsigned long rGameTime::TimeDeltaMilliseconds() const{
	return m_timeDeltaMilliseconds;
}

#endif