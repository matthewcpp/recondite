#ifndef R_TIME_HPP
#define R_TIME_HPP

class rTime{
public:
	rTime();

	void Start(unsigned long seedTime);
	void Update(unsigned long currentTime);

	inline unsigned long RunningTime() const;
	inline float TimeDeltaSeconds() const;
	inline unsigned long TimeDeltaMilliseconds() const;
	inline unsigned long LastUpdateTime() const;

private:

	void Init();

	unsigned long m_runningTime;
	unsigned long m_lastUpdateTime;

	float m_timeDeltaSeconds;
	unsigned long m_timeDeltaMilliseconds;
};

unsigned long rTime::LastUpdateTime() const{
	return m_lastUpdateTime;
}

unsigned long rTime::RunningTime() const{
	return m_runningTime;
}

float rTime::TimeDeltaSeconds() const{
	return m_timeDeltaSeconds;
}

unsigned long rTime::TimeDeltaMilliseconds() const{
	return m_timeDeltaMilliseconds;
}

#endif
