#ifndef R_ANIMATIONCURVE_HPP
#define R_ANIMATIONCURVE_HPP

#include <vector>
template <class T>

struct rKeyframe{
	rKeyframe(float time, const T& value) : time(time), value(value){}
	
	float time;
	T value;
};

template <class T>
class rAnimationCurve{
public:
	typedef rKeyframe<T> KeyType;

public:
	size_t NumKeys() const { return m_keys.size();}
	void Clear() {m_keys.clear();}

	void AddKey(float time, const T& value);
	KeyType* GetKey(size_t index);

	bool DetermineKeyframes(float animationTime, size_t& start, size_t& end) const;


private:
	typedef std::vector<KeyType> KeyVector;
	KeyVector m_keys;
};

template <class T>
void rAnimationCurve<T>::AddKey(float time, const T& value){
	KeyType key(time, value);
	m_keys.push_back(key);
}

template <class T>
typename rAnimationCurve<T>::KeyType* rAnimationCurve<T>::GetKey(size_t index){
	if (index >= m_keys.size())
		return NULL;
	else
		return &m_keys[index];
}

template <class T>
bool rAnimationCurve<T>::DetermineKeyframes(float animationTime, size_t& start, size_t& end) const{
	if (m_keys.size() == 0){
		return false;
	}
	else if (animationTime < 0.0f){
		start = end = 0;
		return true;
	}
	else{
		start = 0;

		for (size_t i = start + 1; i < m_keys.size(); i ++){
				if (animationTime >= m_keys[i].time)
					start = i;
				else 
					break;
			}

		if (start >= m_keys.size() - 1){
			end = start;
		}
		else{
			end = start + 1;
		}

		return true;
	}
}

#endif