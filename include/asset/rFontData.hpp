#pragma once

#include "rBuild.hpp"

#include "stream/rOStream.hpp"
#include "stream/rIStream.hpp"

#include "asset/rTextureData.hpp"
#include "asset/rFont.hpp"

namespace recondite {
	/**
	Class representing Font Family Data to be loaded into the engine
	*/
	class RECONDITE_API FontData {
	public:
		FontData();
		~FontData();

		/**
		Gets the font family object
		\returns the font family
		*/
		Font::Family* GetFamily();

		/**
		Detaches the font family from this object.  It is the responsibility of the caller to delete the returned object.
		After a call to this method the object should no longer be used.
		\returns the font family
		*/
		Font::Family* ReleaseFamily();

		/**
		Gets the texture data containing the rendered glyphs for this font family.
		\returns the texture data
		*/
		rTextureData* GetTextureData();

	public:
		/**
		Reads the font family from an input stream
		\param stream input stream
		\returns 0 on success, non zero on failure
		*/
		int Read(rIStream& stream);

		/**
		Writes the font family to an input stream
		\param stream output stream
		\returns 0 on success, non zero on failure
		*/
		int Write(rOStream& stream);

	private:
		struct Impl;
		Impl* _impl;
	};
}