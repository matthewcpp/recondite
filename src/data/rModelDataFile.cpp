#include "data/rModelDataFile.hpp"

rContentError rModelDataWriter::WriteToFile(const rString& dir, const rModelData& modelData){
	rString modelName = modelData.GetName();

	rXMLDocument document;
	document.CreateRoot("model");
	document.GetRoot()->CreateChild("name", modelName);
	
	rAlignedBox3 boundingBox = modelData.GetBoundingBox();
	rXMLUtil::CreateAlignedBox3Element(document.GetRoot(), "boundingBox", boundingBox);

	rSkeleton* skeleton = modelData.GetSkeleton();
	if (skeleton)
		document.GetRoot()->CreateChild("skeleton", modelName);

	
	rXMLElement* meshes = document.GetRoot()->CreateChild("meshes");

	rArrayString meshNames; 
	modelData.GetMeshDataNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMeshData* meshData = modelData.GetMeshData(meshNames[i]);

		rXMLElement* meshNode = meshes->CreateChild("mesh");
		meshNode->CreateChild<rString>("name",meshData->name);
		meshNode->CreateChild("material", meshData->material);
		meshNode->CreateChild("buffer", meshData->buffer);

		rXMLUtil::CreateAlignedBox3Element(meshNode, "boundingBox", meshData->boundingBox);
	}

	document.WriteToFile(rPath::Assemble(dir, modelName, "rmdl"));
	WriteDependencies (dir, modelData);

	return rCONTENT_ERROR_NONE;
}

rContentError rModelDataWriter::WriteDependencies(const rString& dir, const rModelData& modelData){
	rString modelName = modelData.GetName();

	rGeometryDataWriter writer;
	writer.WriteToFile(rPath::Assemble(dir, modelName, "rgeo"), *modelData.GetGeometryData());

	rArrayString names;
	modelData.GetTextureDataNames(names);

	for (size_t i = 0; i < names.size(); i++){
		rTexture2DData* texData = modelData.GetTextureData(names[i]);
		texData->WriteToPath(rPath::Assemble(dir, names[i], "rtex"));
	}

	names.clear();
	modelData.GetMaterialDataNames(names);

	for (size_t i = 0; i < names.size(); i++){
		rMaterialData* matData = modelData.GetMaterialData(names[i]);
		matData->WriteToPath(rPath::Assemble(dir, names[i], "rmat"));
	}

	rSkeleton* skeleton = modelData.GetSkeleton();
	if (skeleton){
		rSkeletonData skeletonData;
		skeletonData.WriteToFile(rPath::Assemble(dir, modelName, "rskl"), *skeleton);
	}

	return rCONTENT_ERROR_NONE;
}

rContentError rModelDataReader::LoadFromFile(const rString& path, rModelData& modelData){
	rIFileStream file (path.c_str());
	rContentError error =  LoadFromStream(file, modelData);
	modelData.SetPath(path);

	return error;
}

rContentError rModelDataReader::LoadFromStream(rIStream& stream, rModelData& modelData){
	rAlignedBox3 boundingBox;
	rXMLDocument document;

	modelData.Clear();
	document.LoadFromStream(stream);

	modelData.SetName(document.GetRoot()->GetFirstChildNamed("name")->Text());
	
	rXMLUtil::ReadAlignedBox3FromFromElement(document.GetRoot()->GetFirstChildNamed("boundingBox"), boundingBox);
	modelData.SetBoundingBox(boundingBox);
	
	rXMLElement* meshesNode = document.GetRoot()->GetFirstChildNamed("meshes");

	for (size_t i = 0; i < meshesNode->NumChildren(); i++){
		rXMLElement* meshNode = meshesNode->GetChild(i);

		rMeshData* meshData = modelData.CreateMeshData(meshNode->GetFirstChildNamed("name")->Text());
		meshData->buffer = meshNode->GetFirstChildNamed("buffer")->Text();
		meshData->material = meshNode->GetFirstChildNamed("material")->Text();
		rXMLUtil::ReadAlignedBox3FromFromElement(meshNode->GetFirstChildNamed("boundingBox"), meshData->boundingBox);
	}
	
	return rCONTENT_ERROR_NONE;
}