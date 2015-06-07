#include "asset/rGeometryManager.hpp"

rGeometryManager::rGeometryManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rAssetManager < rGeometry, rGeometryData, rGeometryFile >(fileSystem)
{
	m_graphicsDevice = graphicsDevice;
}

rGeometry* rGeometryManager::CreateAssetFromData(const rGeometryData& geometryData, const rString& name){
	unsigned int vertexBuffer = m_graphicsDevice->CreateArrayBuffer((const char*)geometryData.VertexData(), geometryData.VertexDataSize());
	unsigned int boneLinkBuffer = 0;

	rGeometry* geometry = new rGeometry(name, geometryData.GeometryProfile(), vertexBuffer, boneLinkBuffer);

	//TODO: use foreach interface?
	rArrayString bufferNames;
	geometryData.GetElementBufferNames(bufferNames);

	for (size_t i = 0; i < bufferNames.size(); i++){
		rElementBufferData* buffer = geometryData.GetElementBuffer(bufferNames[i]);

		unsigned int elementBufferId = m_graphicsDevice->CreateElementBuffer(buffer->GetElementData(), buffer->ElementDataSize());
		geometry->AddElementBuffer(bufferNames[i], elementBufferId, buffer->ElementCount(), buffer->GeometryType());
	}

	return geometry;
}

void rGeometryManager::DisposeAsset(rGeometry* geometry) {
	m_graphicsDevice->DeleteBuffer(geometry->VertexBufferId());

	//TODO: use foreach interface?
	rArrayString bufferNames;
	const rElementBuffer* elementBuffer = NULL;
	geometry->GetElementBufferNames(bufferNames);

	for (size_t i = 0; i < bufferNames.size(); i++){
		elementBuffer = geometry->GetElementBuffer(bufferNames[i]);
		m_graphicsDevice->DeleteBuffer(elementBuffer->BufferId());
	}
}