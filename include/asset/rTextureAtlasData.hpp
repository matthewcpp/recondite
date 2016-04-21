#ifndef R_TEXTUREATLAS_HPP
#define R_TEXTUREATLAS_HPP

#include <vector>
#include <memory>

#include "rDefs.hpp"
#include "rBuild.hpp"
#include "rString.hpp"
#include "rVector2.hpp"
#include "rSize.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"



class RECONDITE_API rTextureAtlasData {
public:
	struct Entry {
		Entry();
		Entry(const rString& _name, const rSize& _textureSize, const rVector2& _uvOrigin, const rVector2& _uvSize);

		rString name;
		rSize textureSize;
		rVector2 uvOrigin;
		rVector2 uvSize;
	};

public:
	rTextureAtlasData();
	~rTextureAtlasData();

	void AddEntry(const rString& name, const rSize& textureSize, const rVector2& uvOrigin, const rVector2& uvSize);
	const Entry* GetEntry(size_t index) const;
	size_t GetNumEntries() const;
	void Clear();

public:
	int Read(rIStream& stream);
	int Write(rOStream& stream);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};



#endif