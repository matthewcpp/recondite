#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <map>
#include <fstream>
#include <utility>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rAlignedBox3.hpp"
#include "rTexCoordGeometryData.hpp"
#include "rVertexColorGeometryData.hpp"
#include "rPrimitiveGeometryData.hpp"
#include "rMaterialData.hpp"

struct RECONDITE_API rMeshData{
	rMeshData(const rString& mName, const rString& bufferName, rGeometryType geoType)
		:meshName(mName), elementBufferName(bufferName), geometryType(geoType) {}

	rString meshName;
	rString elementBufferName;
	rMaterialData materialData;

	rAlignedBox3 boundingBox;
	rGeometryType geometryType;

};

class RECONDITE_API rModelData{
public:
	rModelData(rGeometryProfile geometryProfile);

	void CreateMeshDataFromGeometry();
	void RecalculateMeshBoundingBoxes();

	rMeshData* GetMeshData(const rString& name);
	void GetMeshDataNames(rArrayString& names) const;

	rGeometryData* GetGeometryData();

	virtual void Clear();

private:
	void RecalulateMeshDataBounding(rMeshData* meshData);
	void InitWithProfile(rGeometryProfile geometryProfile);

private:
	
	std::unique_ptr<rGeometryData> m_geometryData;
	std::map<rString, std::shared_ptr<rMeshData>> m_meshes;

	rNO_COPY_CLASS(rModelData)
};

#endif
