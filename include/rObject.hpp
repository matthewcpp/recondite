#ifndef R_OBJECT_HPP
#define R_OBJECT_HPP

#include "rBuild.hpp"
#include "rString.hpp"
#include "rEngine.hpp"
#include "rDefs.hpp"

/**
	Base class for all objects that can exist in the scene.  All objects have an update method that is invoked on every game tick.
*/
class RECONDITE_API rObject {
public:
	rObject(const rString& id, rEngine* engine) : m_id(id), m_engine(engine) {}
	virtual ~rObject() {}

public:
	/**
	Gets the unique identifier for this object.
	\returns Object's unique Identifier
	*/
	rString Id() const {return m_id;}

	/**
	Sets the unique Id for this object.  Normally this method should not be called directly.
	\param new Identifier for this this object.
	*/
	void SetId(const rString& id) { m_id = id; }

	/**
	This method is called each tick.
	*/
	virtual void Update() {}

	/**
	Called when an object is removed from the scene
	*/
	virtual void OnDelete() {};

protected:
	rEngine* m_engine;

private:
	rString m_id;

	rNO_COPY_CLASS(rObject)
};

#endif