#ifndef R_ACTOR3_HPP
#define R_ACTOR3_HPP

#include <memory>

#include "rBuild.hpp"
#include "rVector3.hpp"
#include "rQuaternion.hpp"
#include "rObject.hpp"
#include "rBehavior.hpp"

#include "rEngine.hpp"

#include "rRenderingOptions.hpp"

#include "rAlignedBoxBoundingVolume.hpp"
#include "rPropertyCollection.hpp"

#include "interface/riSerialization.hpp"

/**
This is the base class for all objects that occupy space in the scene.
*/
class RECONDITE_API rActor3 : public rObject{
public:
	rActor3(const rString& id, rEngine* engine);

	virtual void Draw();
	virtual void Update();

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
	virtual riBoundingVolume* BoundingVolume() const;
	void SetBoundingVolume(riBoundingVolume* boundingVolume);
	rAlignedBox3 WorldBounding();

	bool Pickable() const;
	void SetPickable(bool pickable);
	virtual bool RayPick(const rRay3& ray, rPickResult& result);

	rRenderingOptions* RenderingOptions();

	rPropertyCollection& CustomProperties();

	rVector3 Forward() const;
	rVector3 Backward() const;
	rVector3 Left() const;
	rVector3 Right() const;
	rVector3 Up() const;
	rVector3 Down() const;

	virtual bool IsDrawable() const;

	virtual size_t GetNumAssets() const = 0;
	virtual bool GetAsset(size_t index, rAssetType& assetType, rString& name) const = 0;
	virtual bool ShouldPersist() const;
	virtual void SetShouldPersist(bool shouldPersist);

public:
	bool CreateBehavior(const rString& className);
	void ClearBehavior();

public:
	virtual bool Save(riSerializationTarget* target) final;
	virtual bool Load(riSerializationTarget* target) final;

protected:
	virtual bool DoSerialize(riSerializationTarget* target, rSerializeAction action);
	virtual void OnSave();
	virtual void OnLoad();

protected:

	void SetTransformed(bool transformed = true);

	void RecalculateTransform();

protected:

	rVector3 m_position;
	rVector3 m_rotation;
	rVector3 m_scale;

	rMatrix4 m_transform;
	rPropertyCollection m_customProperties;
	rRenderingOptions m_renderingOptions;

	std::unique_ptr<riBoundingVolume> m_boundingVolume;
	std::unique_ptr<recondite::Behavior> m_behavior;

private:

	bool m_hasTransformed;
	bool m_pickable;
	bool m_persist;

	rNO_COPY_CLASS(rActor3)
};

#endif