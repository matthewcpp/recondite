#include "Converter.hpp"

#include "rFileSystem.hpp"
#include "rPath.hpp"

#include "ImageImporter.hpp"
#include "asset/rTextureData.hpp"

#include "TextureAtlasImporter.hpp"
#include "asset/rTextureAtlasData.hpp"

#include "FontImporter.hpp"

#include <iostream>

namespace recondite { namespace tools {
	int Converter::Main(int argc, char** argv) {
		using namespace lambda_options::with_char;

		Options opts;

		opts.AddOption(Keyword("texture", "t"), [&](std::string inputfile) {
			this->ConvertImage(inputfile.c_str());
		});

		opts.AddOption(Keyword("texture-atlas", "ta"), [&](std::string manifest) {
			this->CreateTextureAtlas(manifest.c_str());
		});

		opts.AddOption(Keyword("font", "f"), [&](std::string manifest){
			this->ConvertFont(manifest.c_str());
		});

		auto parseContext = opts.CreateParseContext(argv + 1, argv + argc);

		try {
			parseContext.Run();
		}
		catch (ParseFailedException const &) {
			return 1;
		}

		return 0;
	}

	int Converter::ConvertImage(const rString& path) {
		std::cout << "convert texture: " << path << std::endl;

		import::ImageImporter imageImporter;

		rTextureData textureData;
		int error = imageImporter.ImportImage(path, textureData);

		if (error) {
			std::cout << "texture conversion failed." << std::endl;
		}
		else {
			rString outDir, outName;
			rPath::Split(path, &outDir, &outName, nullptr);

			rString outPath = rPath::Assemble(outDir, outName, "rtex");
			std::cout << "saving file: " << outPath << std::endl;

			auto outFile = m_fileSystem.GetWriteFileRef(outPath);
			textureData.Write(*outFile);
		}

		return error;
	}

	int Converter::CreateTextureAtlas(const rString& path) {
		std::cout << "Generate Texture Atlas from manifest: " << path << std::endl;

		import::TextureAtlasImporter textureAtlas;
		int error = textureAtlas.ReadManifestFromPath(path);

		if (error) {
			std::cout << "texture atlas parse failed." << std::endl;
		}
		else {
			rTextureAtlasData textureAtlasData;
			rTextureData textureData;

			error = textureAtlas.GenerateAtlas(textureAtlasData, textureData);

			if (error){
				std::cout << "texture atlas generation failed." << std::endl;
			}
			else{
				rString outDir, outName;
				rPath::Split(path, &outDir, &outName, nullptr);

				rString atlasOutPath = rPath::Assemble(outDir, outName, "ratl");
				rString textureOutPath = rPath::Assemble(outDir, outName, "rtex");

				rOFileStream atlasFile(atlasOutPath);
				textureAtlasData.Write(atlasFile);

				auto outFile = m_fileSystem.GetWriteFileRef(textureOutPath);
				textureData.Write(*outFile);
			}
		}

		return error;
	}

	int Converter::ConvertFont(const rString& path){
		std::cout << "Generate Font from file: " << path << std::endl;

		import::FontImporter fontImporter;
		int error = fontImporter.ReadManifestFromPath(path);

		if (error){
			std::cout << "font file parse failed." << std::endl;
		}
		else{
			rFontData fontData;
			rTextureData textureData;

			error = fontImporter.GenerateFont(fontData, textureData);

			rString outDir, outName;
			rPath::Split(path, &outDir, &outName, nullptr);
			rString textureOutPath = rPath::Assemble(outDir, outName, "rtex");

			auto outFile = m_fileSystem.GetWriteFileRef(textureOutPath);
			textureData.Write(*outFile);
		}

		return error;
	}
}}