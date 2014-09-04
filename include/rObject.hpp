#ifndef R_OBJECT_HPP
#define R_OBJECT_HPP

#include "rBuild.hpp"
#include "rString.hpp"
#include "rEngine.hpp"

class RECONDITE_API rObject {
public:
	rObject(const rString& id, rEngine* engine) : m_id(id), m_engine(engine) {}
	~rObject() {}

public:
	rString Id() const {return m_id;}

protected:
	rEngine* m_engine;

private:
	rString m_id;
};

#endif