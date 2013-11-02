#ifndef R_SKELETONDATA_HPP
#define R_SKELETONDATA_HPP

#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rSkeleton.hpp"

class rSkeletonData{
public:
	rContentError ReadFromFile(const rString& path, rSkeleton& skeleton);
	rContentError ReadFromStream(std::istream& stream, rSkeleton& skeleton);

	rContentError WriteToFile(const rString& path, const rSkeleton& skeleton);
	rContentError WriteToStream(std::ostream& stream, const rSkeleton& skeleton);

private:
	void WriteHeader(std::ostream& stream, const rSkeleton& skeleton);
	void WriteBones(std::ostream& stream, const rSkeleton& skeleton);
	void WriteAnimations(std::ostream& stream, const rSkeleton& skeleton);

	void ReadHeader(std::istream& stream, rSkeleton& skeleton);
	void ReadBones(std::istream& stream, rSkeleton& skeleton);
	void ReadAnimations(std::istream& stream, rSkeleton& skeleton);
	
private:
	size_t boneCount;
	size_t animationCount;
	
	static const int magicNumber;
	
};

#endif