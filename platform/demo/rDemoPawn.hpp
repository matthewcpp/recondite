#ifndef R_DEMOPAWN_HPP
#define R_DEMOPAWN_HPP

#include "rPawn.hpp"
#include "data/rGeometryData.hpp"

typedef std::map<rString, rImmediateBuffer*> rImmediateBufferMap;

class rDemoPawn : public rPawn{
public:
	rDemoPawn(rModel* model, const rString& name , const rVector3& position);

	virtual void Draw(rEngine& engine);

	void SetModel(rModel* model);

private:
	void SetupImmediateBuffer(const rString name);

private:
	rGeometryData m_geometryData;
	rImmediateBufferMap m_buffers;

};

#endif