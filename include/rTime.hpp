#ifndef R_TIME_HPP
#define R_TIME_HPP

class rTime{
public:
	rTime();

	void Start(unsigned long seedTime);
	void Update(unsigned long currentTime);

	inline unsigned long Time() const;
	inline float TimeDeltaSeconds() const;
	inline unsigned long TimeDeltaMilliseconds() const;

private:

	void Init();

	unsigned long m_gameTime;
	unsigned long m_lastUpdateTime;

	float m_timeDeltaSeconds;
	unsigned long m_timeDeltaMilliseconds;
};

unsigned long rTime::Time() const{
	return m_gameTime;
}

float rTime::TimeDeltaSeconds() const{
	return m_timeDeltaSeconds;
}

unsigned long rTime::TimeDeltaMilliseconds() const{
	return m_timeDeltaMilliseconds;
}

#endif