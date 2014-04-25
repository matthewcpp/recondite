#ifndef R_SKELETONDATA_HPP
#define R_SKELETONDATA_HPP

#include <fstream>

#include "rBuild.hpp"
#include "rString.hpp"

#include "rSkeleton.hpp"

class RECONDITE_API rSkeletonData{
public:
	rContentError ReadFromFile(const rString& path, rSkeleton& skeleton);
	rContentError ReadFromStream(std::istream& stream, rSkeleton& skeleton);

	rContentError WriteToFile(const rString& path, const rSkeleton& skeleton);
	rContentError WriteToStream(std::ostream& stream, const rSkeleton& skeleton);

	rString GetPath() const;
	void SetPath(const rString& path);

private:
	void WriteHeader(std::ostream& stream, const rSkeleton& skeleton);
	void WriteBones(std::ostream& stream, const rSkeleton& skeleton);
	void WriteAnimations(std::ostream& stream, const rSkeleton& skeleton);

	void ReadHeader(std::istream& stream, rSkeleton& skeleton);
	void ReadBones(std::istream& stream, rSkeleton& skeleton);
	void ReadAnimations(std::istream& stream, rSkeleton& skeleton);

	void WriteAnimationCurve(const char* curveData, size_t keyCount, size_t keySize, std::ostream& stream);
	
private:
	size_t boneCount;
	size_t animationCount;
	
	static const int magicNumber;
	
	rString m_path;

};

#endif
