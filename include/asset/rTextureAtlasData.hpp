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
#include "xml/rXMLDocument.hpp"



class RECONDITE_API rTextureAtlasData {
public:
	void AddEntry(const rString& name, const rSize& textureSize, const rVector2& uvOrigin, const rVector2& uvSize);
	size_t GetNumEntries() const;
	void Clear();

public:
	rContentError Read(rIStream& stream);
	rContentError Write(rOStream& stream);

public:
	struct rTextureAtlasEntry {
		rTextureAtlasEntry() {}
		rTextureAtlasEntry(const rString& _name, const rSize& _textureSize, const rVector2& _uvOrigin, const rVector2& _uvSize)
			:name(_name), textureSize(_textureSize), uvOrigin(_uvOrigin), uvSize(_uvSize) {}

		rString name;
		rSize textureSize;
		rVector2 uvOrigin;
		rVector2 uvSize;
	};

private:
	typedef std::shared_ptr<rTextureAtlasEntry> rTextureEntryRef;
	typedef std::vector<rTextureEntryRef> rTextureEntryArray;

	rTextureEntryArray m_textureEntries;
};



#endif