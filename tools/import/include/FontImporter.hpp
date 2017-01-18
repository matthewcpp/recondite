#pragma once

#include <memory>
#include <cstdint>

#include "BuildImport.hpp"
#include "rString.hpp"

#include "stream/rIFileStream.hpp"
#include "asset/rFont.hpp"
#include "asset/rTextureData.hpp"
#include "asset/rFontData.hpp"

namespace recondite { namespace import {

	/**
	<P>This class is used in order to import fonts.  A Font may be imported with one or more faces.  
	A face describes the size, style and path of the font.
	Faces may be either added manually or read from a manifest file.
	</P>
	<p>A Sample Manifest File is illustarted below:</p>
	<PRE>
	<font>
		<faces>
			<face>
				<size>14</size>
				<style>Normal</style>
				<path>Consolas/consola.ttf</path>
			</face>
		</faces>
	</font>
	</PRE>
	*/
	class RECONDITE_IMPORT_API FontImporter{
	public:
		FontImporter();
		~FontImporter();

	public:
		/**
		Specifies a base directory to use when resolving a face description's path.
		\param assetPrefix base path to use when resolving font file paths.
		*/
		void SetAssetPathPrefix(const rString& assetPrefix);

		/**
		Specifies a face which will be imported.
		\param path relative path from base directory of the font file.
		\param size the pixel size of this face.
		\param style the style to use for this face.
		\returns zero on success non zero on error.
		*/
		int AddFaceDescription(const rString& path, uint16_t size, Font::Style style);

	public:
		/**
		Reads a manifest file from disk.  This method will automatically set the asset prefix to the directory from which the manifest file was read.
		\param path the file for the manifest file to read.
		\returns zero on success non zero on error.
		*/
		int ReadManifestFromPath(const rString& path);

		/**
		Reads a manifest file from a stream.
		\param stream the stream from which thethe manifest file will be read.
		\returns zero on success non zero on error.
		*/
		int ReadManifestFromStream(rIStream& stream);

		/**
		Generates the glyph and texture data for all specified faces.
		\param fontData data object which will be populated with font data
		\returns zero on success non zero on error.
		*/
		int GenerateFont(FontData& fontData);

	private:
		struct Impl;
		Impl* _impl;
	};

}}