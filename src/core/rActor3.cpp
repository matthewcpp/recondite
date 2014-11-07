#include "rActor3.hpp"

rActor3::rActor3(const rString& id, rEngine* engine)
	:rObject(id, engine)
{
	m_position = rVector3::ZeroVector;
	m_rotation = rVector3::ZeroVector;
	m_scale = rVector3::OneVector;
}

int rActor3::Update(){
	return 0;
}

void rActor3::Draw(){
}

void rActor3::MoveForward(float amount){
	rVector3 forward = Forward();
	forward *= amount;
	m_position += forward;
}

void rActor3::MoveBackward(float amount){
	rVector3 backward = Backward();
	backward *= amount;
	m_position += backward;
}

void rActor3::MoveLeft(float amount){
	rVector3 left = Left();
	left *= amount;
	m_position += left;
}

void rActor3::MoveRight(float amount){
	rVector3 right = Right();
	right *= amount;
	m_position += right;
}

void rActor3::MoveUp(float amount){
	rVector3 up = Up();
	up *= amount;
	m_position += up;
}

void rActor3::MoveDown(float amount){
	rVector3 down = Down();
	down *= amount;
	m_position += down;
}

rVector3 rActor3::Forward() const{
	rVector3 forward = rVector3::ForwardVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(forward);
	forward.Normalize();

	return forward;
}

rVector3 rActor3::Backward() const{
	rVector3 back = rVector3::BackwardVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(back);
	back.Normalize();

	return back;
}

rVector3 rActor3::Left() const{
	rVector3 left = rVector3::LeftVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(left);
	left.Normalize();

	return left;
}

rVector3 rActor3::Right() const{
	rVector3 right = rVector3::RightVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(right);
	right.Normalize();

	return right;
}

rVector3 rActor3::Up() const{
	rVector3 up = rVector3::UpVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(up);
	up.Normalize();

	return up;
}

rVector3 rActor3::Down() const{
	rVector3 down = rVector3::DownVector;
	rQuaternion q(m_rotation);
	q.TransformVector3(down);
	down.Normalize();

	return down;
}

void rActor3::SetPosition(const rVector3& position){
	m_position = position;
}

void rActor3::SetPosition(float x, float y, float z){
	m_position.Set(x,y,z);
}

rVector3 rActor3::Position() const{
	return m_position;
}

void rActor3::SetScale(const rVector3& scale){
	m_scale = scale;
}

void rActor3::SetUniformScale(float k){
	m_scale.Set(k, k, k);
}

rVector3 rActor3::Scale() const{
	return m_scale;
}

void rActor3::SetRotation(const rVector3& rotation){
	m_rotation = rotation;
}

rVector3 rActor3::Rotation() const{
	return m_rotation;
}

rMatrix4 rActor3::TransformMatrix() const{
	rMatrix4 translate, rotate, scale;
	translate.SetTranslate(m_position);

	rQuaternion q(m_rotation);
	rMatrixUtil::QuaterionToMatrix(q, rotate);

	scale.SetScale(m_scale);

	rMatrix4 result = translate * scale * rotate;
	return result;
}