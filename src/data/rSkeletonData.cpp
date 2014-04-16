#include "data/rSkeletonData.hpp"

const int rSkeletonData::magicNumber = 1818981234;

rString rSkeletonData::GetPath() const{
	return m_path;
}

void rSkeletonData::SetPath(const rString& path){
	m_path = path;
}

rContentError rSkeletonData::WriteToFile(const rString& path, const rSkeleton& skeleton){
	std::ofstream file(path.c_str(), std::ios::binary);

	return rSkeletonData::WriteToStream(file, skeleton);
}

rContentError rSkeletonData::WriteToStream(std::ostream& stream, const rSkeleton& skeleton){
	if (stream){

		WriteHeader(stream, skeleton);
		WriteBones(stream, skeleton);
		WriteAnimations(stream, skeleton);

		return rCONTENT_ERROR_NONE;
	}
	else{
		return rCONTENT_ERROR_STREAM_ERROR;
	}
}

void rSkeletonData::WriteHeader(std::ostream& stream, const rSkeleton& skeleton){
	boneCount = skeleton.NumBones();
	animationCount = skeleton.NumAnimations();

	stream.write((char*)&magicNumber, 4);
	stream.write((char*)&boneCount, 4);
	stream.write((char*)&animationCount, 4);
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

void rSkeletonData::WriteAnimationCurve(const char* curveData, size_t keyCount, size_t keySize, std::ostream& stream){
	stream.write((char*)&keyCount, 4);
	stream.write(curveData, keyCount * keySize);
}

void rSkeletonData::WriteAnimations(std::ostream& stream, const rSkeleton& skeleton){
	rArrayString animationNames;
	skeleton.GetAnimationNames(animationNames);

	size_t size, trackCount;
	rString name;
	float duration;

	for (size_t i = 0; i < animationNames.size(); i++){
		rAnimation* animation = skeleton.GetAnimation(animationNames[i]);

		name = animation->Name();
		size = name.length();
		duration = animation->Duration();
		trackCount = animation->NumTracks();

		stream.write((char*)&size, 4);
		stream.write(name.c_str(), size);
		stream.write((char*)&duration, 4);
		stream.write((char*)&trackCount, 4);

		for (unsigned short b = 0; b < skeleton.NumBones(); b++){
			rAnimationTrack* track = animation->GetTrack(b);
			

			if (track){
				stream.write((char*)&b, 2);

				rVector3AnimationCurve& translateCurve = track->TranslationCurve();
				WriteAnimationCurve(translateCurve.GetConstDataPointer(), translateCurve.NumKeys(), sizeof(rVector3AnimationCurve::KeyType), stream);

				rQuaternionAnimationCurve& rotationCurve = track->RotationCurve();
				WriteAnimationCurve(rotationCurve.GetConstDataPointer(), rotationCurve.NumKeys(), sizeof(rQuaternionAnimationCurve::KeyType), stream);

				rVector3AnimationCurve& scaleCurve = track->ScaleCurve();
				WriteAnimationCurve(scaleCurve.GetConstDataPointer(), scaleCurve.NumKeys(), sizeof(rVector3AnimationCurve::KeyType), stream);
			}
		}
	}
}

rContentError rSkeletonData::ReadFromFile(const rString& path, rSkeleton& skeleton){
	std::ifstream file(path.c_str(), std::ios::binary);

	return rSkeletonData::ReadFromStream(file, skeleton);
}

rContentError rSkeletonData::ReadFromStream(std::istream& stream, rSkeleton& skeleton){
	skeleton.Clear();

	if (stream){
		ReadHeader(stream, skeleton);
		ReadBones(stream, skeleton);
		ReadAnimations(stream, skeleton);

		return rCONTENT_ERROR_NONE;
	}
	else{
		return rCONTENT_ERROR_STREAM_ERROR;
	}
}


void rSkeletonData::ReadHeader(std::istream& stream, rSkeleton& skeleton){
	int magicNum;

	stream.read((char*)&magicNum, 4);
	stream.read((char*)&boneCount, 4);
	stream.read((char*)&animationCount, 4);
}

void rSkeletonData::ReadBones(std::istream& stream, rSkeleton& skeleton){
	char buffer[1024];
	int id,parentId;
	size_t nameLen, hierarchyCount;
	rString name, parent;
	
	for (size_t i = 0; i < boneCount; i++){
		stream.read((char*)&id, 4);

		stream.read((char*)&nameLen, 4);
		stream.read((char*)buffer, nameLen);
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

	skeleton.CalculateInverseBoneTransformations();
}

void rSkeletonData::ReadAnimations(std::istream& stream, rSkeleton& skeleton){
	char buffer[256];
	size_t size, trackCount;
	rString name;
	float duration;
	unsigned short handle;

	for (size_t i = 0; i < animationCount; i++){
		stream.read((char*)&size , 4);
		stream.read(buffer, size);
		stream.read((char*)&duration, 4);
		stream.read((char*)&trackCount, 4);

		name.assign(buffer, size);

		rAnimation* animation = skeleton.CreateAnimation(name);
		animation->SetDuration(duration);

		for (size_t i = 0; i < trackCount; i++){
			stream.read((char*)&handle , 2);
			rAnimationTrack* track = animation->CreateTrack(handle);

			stream.read((char*)&size , 4);
			rVector3AnimationCurve& translateCurve = track->TranslationCurve();
			translateCurve.AllocateFrames(size);
			stream.read(translateCurve.GetDataPointer(), size * sizeof(rVector3AnimationCurve::KeyType));

			stream.read((char*)&size , 4);
			rQuaternionAnimationCurve& rotationCurve = track->RotationCurve();
			rotationCurve.AllocateFrames(size);
			stream.read(rotationCurve.GetDataPointer(), size * sizeof(rQuaternionAnimationCurve::KeyType));

			stream.read((char*)&size , 4);
			rVector3AnimationCurve& scaleCurve = track->ScaleCurve();
			scaleCurve.AllocateFrames(size);
			stream.read(scaleCurve.GetDataPointer(), size * sizeof(rVector3AnimationCurve::KeyType));
		}
	}
}
