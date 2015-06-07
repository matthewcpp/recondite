#ifndef R_GEOMETRYMANAGER_HPP
#define R_GEOMETRYMANAGER_HPP

#include "rBuild.hpp"
#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"

#include "rGeometry.hpp"
#include "rGeometryData.hpp"
#include "rGeometryFile.hpp"

class RECONDITE_API rGeometryManager : public rAssetManager < rGeometry, rGeometryData, rGeometryFile > {
public:
	rGeometryManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);

protected:
	virtual rGeometry* CreateAssetFromData(const rGeometryData& geometryData, const rString& name) override;
	virtual void DisposeAsset(rGeometry* geometry) override;

private:
	rGraphicsDevice* m_graphicsDevice;
};

#endif