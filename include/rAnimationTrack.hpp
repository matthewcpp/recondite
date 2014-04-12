#ifndef R_ANIMATIONTRACK_CPP
#define R_ANIMATIONTRACK_CPP

#include "rVector3.hpp"
#include "rQuaternion.hpp"
#include "rMatrix4.hpp"

#include "rMatrixUtil.hpp"

#include "rAnimationCurve.hpp"

typedef rAnimationCurve<rVector3> rVector3AnimationCurve;
typedef rAnimationCurve<rQuaternion> rQuaternionAnimationCurve;

class rAnimationTrack{
public:
	rAnimationTrack(unsigned short handle);
	
public:
	unsigned short Handle() const;
	void Clear();
	
	rVector3AnimationCurve& TranslationCurve();
	rVector3AnimationCurve& RotationCurve();
	rVector3AnimationCurve& ScaleCurve();

	unsigned short InterpolateKeyframe(float animationTime, rMatrix4& transform) const;

protected:
	rVector3 InterpolateVector3(const rVector3AnimationCurve& curve, float animationTime) const;
	rQuaternion InterpolateQuaternion(const rQuaternionAnimationCurve& curve, float animationTime) const;
	

private:
	unsigned short m_handle;

	rVector3AnimationCurve m_translationCurve;
	rQuaternionAnimationCurve m_rotationCurve;
	rVector3AnimationCurve m_scaleCurve;
};

#endif