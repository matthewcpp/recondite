#ifndef R_ACTOR3_HPP
#define R_ACTOR3_HPP

#include <memory>

#include "rBuild.hpp"
#include "rVector3.hpp"
#include "rQuaternion.hpp"
#include "rObject.hpp"

#include "rEngine.hpp"

#include "rDrawable.hpp"

#include "rAlignedBoxBoundingVolume.hpp"
#include "rPropertyCollection.hpp"

#include "interface/riSerialization.hpp"

class RECONDITE_API rActor3 : public rObject{
public:
	rActor3(const rString& id, rEngine* engine);

	virtual int Update();
	virtual void Draw();

	virtual void SetPosition(const rVector3& position);
	virtual void SetPosition(float x, float y, float z);
	virtual rVector3 Position() const;

	virtual void SetRotation(const rVector3& rotation);
	virtual rVector3 Rotation() const;

	virtual void SetScale(const rVector3& scale);
	virtual void SetUniformScale(float k);
	virtual rVector3 Scale() const;

	virtual rString ClassName() const = 0;

	virtual rMatrix4& TransformMatrix();
	virtual riBoundingVolume* BoundingVolume();

	rDrawable* Drawable();

	rPropertyCollection& CustomProperties();

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

public:
	virtual bool Save(riSerializationTarget* target) final;
	virtual bool Load(riSerializationTarget* target) final;

protected:
	virtual bool DoSerialize(riSerializationTarget* target);
	virtual void OnSave();
	virtual void OnLoad();

protected:

	void SetTransformed(bool transformed = true);

	void RecalculateTransform();

	virtual void DoRecalculateBoundingVolume();
	virtual riBoundingVolume* DoGetBoundingVolume();

protected:

	rVector3 m_position;
	rVector3 m_rotation;
	rVector3 m_scale;

	rMatrix4 m_transform;
	rPropertyCollection m_customProperties;
	std::shared_ptr<rDrawable> m_drawable;

private:

	bool m_hasTransformed;
};

#endif