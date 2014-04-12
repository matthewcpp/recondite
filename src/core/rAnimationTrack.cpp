#include "rAnimationTrack.hpp"

rAnimationTrack::rAnimationTrack(unsigned short handle){
	m_handle = handle;
}

unsigned short rAnimationTrack::Handle() const{
	return m_handle;
}

void rAnimationTrack::Clear(){
	m_translationCurve.Clear();
	m_rotationCurve.Clear();
	m_scaleCurve.Clear();
}

rVector3 rAnimationTrack::InterpolateVector3(const rVector3AnimationCurve& curve, float animationTime) const{
	size_t start, end;

	curve.DetermineKeyframes(animationTime, start, end);
	rVector3 result;
	if (start != end){
		const rVector3AnimationCurve::KeyType* startKey = curve.GetKey(start);
		const rVector3AnimationCurve::KeyType* endKey = curve.GetKey(end);

		float interpolateVal = rMath::ConvertRange(animationTime, startKey->time, endKey->time, 0.0f, 1.0f);

		result = rVector3::Lerp(startKey->value, endKey->value, interpolateVal);
	}
	else{
		const rVector3AnimationCurve::KeyType* key = curve.GetKey(start);
		result = key->value;
	}

	return result;
}

rQuaternion rAnimationTrack::InterpolateQuaternion(const rQuaternionAnimationCurve& curve, float animationTime) const{
	size_t start, end;

	curve.DetermineKeyframes(animationTime, start, end);
	rQuaternion result;
	if (start != end){
		const rQuaternionAnimationCurve::KeyType* startKey = curve.GetKey(start);
		const rQuaternionAnimationCurve::KeyType* endKey = curve.GetKey(end);

		float interpolateVal = rMath::ConvertRange(animationTime, startKey->time, endKey->time, 0.0f, 1.0f);

		result = rQuaternion::Slerp(startKey->value, endKey->value, interpolateVal);
	}
	else{
		const rQuaternionAnimationCurve::KeyType* key = curve.GetKey(start);
		result = key->value;
	}

	return result;
}

unsigned short rAnimationTrack::InterpolateKeyframe(float animationTime, rMatrix4& transform) const{
	rVector3 translate = InterpolateVector3(m_translationCurve, animationTime);
	rVector3 scale = InterpolateVector3(m_scaleCurve, animationTime);
	rQuaternion rotate = InterpolateQuaternion(m_rotationCurve, animationTime);
	
	rMatrix4 transM, rotM, scaleM;
	
	transM.SetTranslate(translate);
	rMatrixUtil::QuaterionToMatrix(rotate, rotM);
	scaleM.SetScale(scale);

	transform = transM * rotM * scaleM;

	return 0;
}