#include "rDemoPawn.hpp"

rDemoPawn::rDemoPawn(rModel* model, const rString& name , const rVector3& position)
	:rPawn(model, name, position)
{
}

void rDemoPawn::Draw(rEngine& engine){
	rAnimationPlayer* animationPlayer = AnimationPlayer();
	rModel* model = Model();

	const rMatrix4* transformData = animationPlayer->GetTransformData();
	const rVertexBoneLinkMap& boneLinks = m_geometryData.VertexBoneLinks();

	rVector3 position;
	rVector2 texCoord;
	rMatrix4 mat;
	int count;

	for (size_t i =0; i < m_geometryData.VertexCount(); i++){
		m_geometryData.GetVertex(i, &position, &texCoord, NULL);

		rVertexBoneLinkResult result = boneLinks.equal_range(i);

		mat.LoadIdentity();
		count = 0;
		for (rVertexBoneLinkMap::const_iterator it = result.first; it != result.second; ++it){
			const rVertexBoneLink& link = it->second;
			if (count)
				mat += transformData[link.boneIndex] * link.weight;
			else 
				mat = transformData[link.boneIndex] * link.weight;

			count ++;
		}

		mat.TransformVector3(position);

		rImmediateBufferMap::iterator end = m_buffers.end();
		for (rImmediateBufferMap::iterator it = m_buffers.begin(); it != end; ++it){
			it->second->SetVertex(i, position, texCoord);
		}
	}

	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		if (m_buffers.count(mesh->buffer)){
			engine.renderer->RenderBuffer(*m_buffers[mesh->buffer], mesh->material);
		}
	}
}

void rDemoPawn::SetModel(rModel* model){
	rPawn::SetModel(model);
	SetupImmediateBuffer(model->Name());
}

void rDemoPawn::SetupImmediateBuffer(const rString name){
	rString file = "content/models/" + name + "/" + name + ".rgeo";
	rGeometryDataReader reader;
	reader.ReadFromFile(file, m_geometryData);

	for (rImmediateBufferMap::iterator it = m_buffers.begin(); it != m_buffers.end(); ++it)
		delete it->second;
	
	m_buffers.clear();

	rArrayString elementBuffers;
	m_geometryData.GetElementBufferNames(elementBuffers);

	for (size_t i = 0; i < elementBuffers.size(); i++){
		rElementBufferData* bufferData = m_geometryData.GetElementBuffer(elementBuffers[i]);

		rImmediateBuffer* buffer = new rImmediateBuffer(rGEOMETRY_TRIANGLES, 3, true);
		buffer->Allocate(m_geometryData.VertexCount());
		buffer->SetIndexBuffer(bufferData->GetElementData(), bufferData->ElementCount());

		m_buffers[elementBuffers[i]] = buffer;
	}
}