#ifndef R_OBJECT_HPP
#define R_OBJECT_HPP

#include "rBuild.hpp"
#include "rString.hpp"
#include "rEngine.hpp"
#include "rDefs.hpp"

class RECONDITE_API rObject {
public:
	rObject(const rString& id, rEngine* engine) : m_id(id), m_engine(engine) {}
	~rObject() {}

public:
	rString Id() const {return m_id;}
	void SetId(const rString& id) { m_id = id; }

protected:
	rEngine* m_engine;

private:
	rString m_id;

rNO_COPY_CLASS(rObject)
};

#endif