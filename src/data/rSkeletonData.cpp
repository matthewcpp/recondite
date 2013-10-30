#include "data/rSkeletonData.hpp"

const int rSkeletonData::magicNumber = 1818981234;

rContentError rSkeletonData::ReadFromFile(const rString& path, rSkeleton& skeleton){
	std::ifstream file(path.c_str(), std::ios::binary);

	return rSkeletonData::ReadFromStream(file, skeleton);
}

rContentError rSkeletonData::ReadFromStream(std::istream& stream, rSkeleton& skeleton){
	skeleton.Clear();

	if (stream){
		ReadHeader(stream, skeleton);
		ReadBones(stream, skeleton);

		return rCONTENT_ERROR_NONE;
	}
	else{
		return rCONTENT_ERROR_STREAM_ERROR;
	}
}

rContentError rSkeletonData::WriteToFile(const rString& path, const rSkeleton& skeleton){
	std::ofstream file(path.c_str(), std::ios::binary);

	return rSkeletonData::WriteToStream(file, skeleton);
}

rContentError rSkeletonData::WriteToStream(std::ostream& stream, const rSkeleton& skeleton){
	if (stream){

		WriteHeader(stream, skeleton);
		WriteBones(stream, skeleton);

		return rCONTENT_ERROR_NONE;
	}
	else{
		return rCONTENT_ERROR_STREAM_ERROR;
	}
}

void rSkeletonData::WriteHeader(std::ostream& stream, const rSkeleton& skeleton){
	size_t boneCount = skeleton.NumBones();

	stream.write((char*)&magicNumber, 4);
	stream.write((char*)&boneCount, 4);
}

void rSkeletonData::WriteBones(std::ostream& stream, const rSkeleton& skeleton){
	rBoneArray hierarchy;

	size_t nameLen;
	rBone* bone = NULL;
	for (size_t i = 0; i <skeleton.NumBones(); i++){
		bone = skeleton.GetBone(i);

		stream.write((char*)&bone->id, 4);

		nameLen = bone->name.length();
		stream.write((char*)&nameLen, 4);
		stream.write(bone->name.c_str(), nameLen);

		stream.write((char*)&bone->position, 12);

		if (bone->parent)
			hierarchy.push_back(bone);
	}

	nameLen = hierarchy.size();
	stream.write((char*)&nameLen, 4);

	for (size_t i = 0; i < hierarchy.size(); i++){
		bone = hierarchy[i];
		
		stream.write((char*)&bone->id, 4);
		stream.write((char*)&bone->parent->id, 4);
	}
}

void rSkeletonData::ReadHeader(std::istream& stream, rSkeleton& skeleton){
	int magicNum;

	stream.read((char*)&magicNum, 4);
	stream.read((char*)&boneCount, 4);
}

void rSkeletonData::ReadBones(std::istream& stream, rSkeleton& skeleton){
	char buffer[1024];
	int id,parentId;
	size_t nameLen, hierarchyCount;
	rString name, parent;
	
	for (size_t i = 0; i < boneCount; i++){
		stream.read((char*)&id, 4);

		stream.read((char*)&nameLen, 4);
		stream.read((char*)&buffer, nameLen);
		name.assign(buffer, nameLen);

		rBone* bone = skeleton.CreateBone(id, name);
		stream.read((char*)&bone->position, 12);
	}

	stream.read((char*)&hierarchyCount, 4);

	for (size_t i =0; i < hierarchyCount; i++){
		stream.read((char*)&id, 4);
		stream.read((char*)&parentId, 4);

		rBone* bone = skeleton.GetBone(id);
		rBone* parentBone = skeleton.GetBone(parentId);

		if (bone && parentBone)
			parentBone->AddChild(bone);
	}
}
