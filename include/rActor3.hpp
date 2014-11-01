#ifndef R_ACTOR3_HPP
#define R_ACTOR3_HPP

#include "rBuild.hpp"
#include "rVector3.hpp"
#include "rQuaternion.hpp"

#include "rEngine.hpp"

class RECONDITE_API rActor3{
public:
	rActor3(const rString& name , const rVector3& position);
	virtual ~rActor3(){}

	virtual int Update(rEngine& engine) { return 0;}
	virtual void Draw(rEngine& engine) {}

	inline void SetPosition(const rVector3& position);
	virtual rVector3 Position() const;

	inline void SetRotation(const rVector3& rotation);
	inline rVector3 Rotation() const;

	inline rString Name() const;

	virtual rString ClassName() const = 0;

	void MoveForward(float amount);
	void MoveBackward(float amount);
	void MoveLeft(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);
	void MoveDown(float amount);

	rVector3 Forward() const;
	rVector3 Backward() const;
	rVector3 Left() const;
	rVector3 Right() const;
	rVector3 Up() const;
	rVector3 Down() const;

protected:
	rString m_name;

	rVector3 m_position;
	rVector3 m_rotation;
};

void rActor3::SetPosition(const rVector3& position){
	m_position = position;
}



rString rActor3::Name() const{
	return m_name;
}

void rActor3::SetRotation(const rVector3& rotation){
	m_rotation = rotation;
}

rVector3 rActor3::Rotation() const{
	return m_rotation;
}

#endif