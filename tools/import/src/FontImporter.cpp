#include "FontImporter.hpp"

#include <vector>
#include <iostream>

#include "rPath.hpp"
#include "xml/rXMLDocument.hpp"
#include "stream/rIFileStream.hpp"
#include "RectPacker.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace recondite { namespace import {
	struct FontGlyphRect : public internal::RectPacker::Item{
		uint32_t scancode;
	};

	struct FaceDescription{
		FaceDescription(){}
		FaceDescription(const rString& _path, uint16_t _size, Font::Style _fontStyle)
			:path(_path), size(_size), fontStyle(_fontStyle){}

		rString path;
		uint16_t size;
		Font::Style fontStyle;
		std::vector<FontGlyphRect> glyphRects;

		FT_Face fontFace;
		Font::Face* faceData;
	};

	struct FontImporter::Impl{
		rString assetPathPrefix;
		std::vector<FaceDescription> faceDescriptions;
		std::vector<uint32_t> scancodes;


		int InitFontFaces(FT_Library freetypeLibrary, Font::Family& fontData);
		int UninitFontFaces(FT_Library freetypeLibrary);

		int GenerateGlyphRects(FT_Library freetypeLibrary, internal::RectPacker& rectPacker, Font::Family& fontData);
		int GenerateGlyphBitmap(FT_Library freetypeLibrary, internal::RectPacker& rectPacker, Font::Family& fontData, rTextureData& textureData);
	};

	FontImporter::FontImporter(){
		_impl = new Impl();

		//temp just use ascii characters
		_impl->scancodes.reserve(127 - 32);
		for (uint32_t i = 32; i < 127; i++){
			_impl->scancodes.push_back(i);
		}
	}

	FontImporter::~FontImporter(){
		delete _impl;
	}

	int FontImporter::ReadManifestFromPath(const rString& path){
		rIFileStream stream(path);

		rPath::Split(path, &_impl->assetPathPrefix, nullptr);

		return ReadManifestFromStream(stream);
	}

	Font::Style GetStyleFromFaceElement(rXMLElement* element){
		rString styleName;
		element->GetChild(1)->GetText(styleName);

		if (styleName == "Bold")
			return Font::Style::Bold;
		else if (styleName == "Italic")
			return Font::Style::Italic;
		else
			return Font::Style::Normal;
	}

	int FontImporter::ReadManifestFromStream(rIStream& stream){
		if (!stream.IsOk()) return 1;

		rXMLDocument doc;
		int error = doc.LoadFromStream(stream);

		if (error) return error;

		rXMLElement* faces = doc.GetRoot()->GetChild(0);
		FaceDescription faceDescription;
		rString text;

		for (size_t i = 0; i < faces->NumChildren(); i++){
			rXMLElement* face = faces->GetChild(i);
			face->GetChild(0)->GetText<uint16_t>(faceDescription.size);
			faceDescription.fontStyle = GetStyleFromFaceElement(face);
			face->GetChild(2)->GetText(faceDescription.path);

			_impl->faceDescriptions.push_back(faceDescription);
		}

		return 0;
	}

	int FontImporter::AddFaceDescription(const rString& path, uint16_t size, Font::Style style){
		_impl->faceDescriptions.push_back(FaceDescription(path, size, style));

		return 0;
	}

	void FontImporter::SetAssetPathPrefix(const rString& assetPrefix){
		_impl->assetPathPrefix = assetPrefix;
	}

	int FontImporter::Impl::InitFontFaces(FT_Library freetypeLibrary, Font::Family& fontData){
		int error = 0;

		for (auto& faceDescription: faceDescriptions){
			faceDescription.faceData = fontData.CreateFace(faceDescription.size, faceDescription.fontStyle);
			
			rString fontFilePath;
			if (assetPathPrefix.empty()){
				fontFilePath = faceDescription.path;
			}
			else{
				fontFilePath = rPath::Combine(assetPathPrefix, faceDescription.path);
			}

			error = FT_New_Face(freetypeLibrary, fontFilePath.c_str(), 0, &faceDescription.fontFace);
			FT_Set_Pixel_Sizes(faceDescription.fontFace, 0, faceDescription.size);

			faceDescription.faceData->SetFaceMetrics(faceDescription.fontFace->size->metrics.height >> 6, faceDescription.fontFace->size->metrics.ascender >> 6, faceDescription.fontFace->size->metrics.descender >> 6);
		}

		return error;
	}

	int FontImporter::Impl::UninitFontFaces(FT_Library freetypeLibrary){
		for (auto& faceDescription: faceDescriptions){
			FT_Done_Face(faceDescription.fontFace);
		}

		return 0;
	}

	int FontImporter::Impl::GenerateGlyphRects(FT_Library freetypeLibrary, internal::RectPacker& rectPacker, Font::Family& fontData){
		int error = 0;

		for (size_t i = 0; i < faceDescriptions.size(); i++){
			FaceDescription& faceDescription = faceDescriptions[i];;
			faceDescription.glyphRects.resize(scancodes.size());

			FT_Set_Pixel_Sizes(faceDescription.fontFace, 0, faceDescription.size);

			//for each scancode, generate a glyph using this face and place it in the rect packer
			for (size_t sc = 0; sc < scancodes.size(); sc++){
				error = FT_Load_Char(faceDescription.fontFace, scancodes[sc], FT_LOAD_RENDER);

				FT_GlyphSlot glyph = faceDescription.fontFace->glyph;
				faceDescription.glyphRects[sc].scancode = scancodes[sc];
				faceDescription.glyphRects[sc].sourceSize.x = glyph->bitmap.width;
				faceDescription.glyphRects[sc].sourceSize.y = glyph->bitmap.rows;
				rectPacker.AddItem(&faceDescription.glyphRects[sc]);
			}
			
		}

		return error;
	}

	int FontImporter::Impl::GenerateGlyphBitmap(FT_Library freetypeLibrary, internal::RectPacker& rectPacker, Font::Family& fontData, rTextureData& textureData){
		int error = 0;
		rSize resultSize = rectPacker.GetResultSize();
		textureData.Allocate(resultSize.x, resultSize.y, 4, rColor::Transparent);

		for (auto& faceDescription : faceDescriptions){
			faceDescription.faceData->AllocateGlyphs(faceDescription.glyphRects.size());

			rVector2 uvOrigin, uvSize;
			for (size_t i = 0; i < faceDescription.glyphRects.size(); i++){
				error = FT_Load_Char(faceDescription.fontFace, faceDescription.glyphRects[i].scancode, FT_LOAD_RENDER);
				FT_GlyphSlot glyph = faceDescription.fontFace->glyph;

				//calculate and store glyph meta data
				rectPacker.CalculatePackedUVForItem(&faceDescription.glyphRects[i], uvOrigin, uvSize);
				faceDescription.faceData->SetGlyph(i, scancodes[i], glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap_top, glyph->bitmap_left, (glyph->advance.x >> 6), uvOrigin, uvSize);
				
				rColor pixel = rColor::White;

				for (int h = 0; h < glyph->bitmap.rows; h++){
					for (int w = 0; w < glyph->bitmap.width; w++){
						int index = (h * glyph->bitmap.width) + w;
						pixel.alpha = glyph->bitmap.buffer[index];

						textureData.SetPixel(faceDescription.glyphRects[i].packedLocation.x + w, faceDescription.glyphRects[i].packedLocation.y + h, pixel);
					}
				}
			}
		}
		return error;
	}

	int FontImporter::GenerateFont(FontData& fontData){
		FT_Library freetypeLibrary;
		
		internal::RectPacker rectPacker;
		rectPacker.SetMaxSize(rSize(1024, 1024));

		int error = FT_Init_FreeType(&freetypeLibrary);
		if (error) return error;

		error = _impl->InitFontFaces(freetypeLibrary, *fontData.GetFamily());
		if (error) return error;

		error = _impl->GenerateGlyphRects(freetypeLibrary, rectPacker, *fontData.GetFamily());
		if (error) return error;
		
		if (!rectPacker.Pack()) return 1;

		error = _impl->GenerateGlyphBitmap(freetypeLibrary, rectPacker, *fontData.GetFamily(), *fontData.GetTextureData());
		if (error) return error;

		error = _impl->UninitFontFaces(freetypeLibrary);
		if (error) return error;

		FT_Done_FreeType(freetypeLibrary);

		return error;
	}
}}

