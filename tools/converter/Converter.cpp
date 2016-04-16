#include "Converter.hpp"

#include "rFileSystem.hpp"
#include "rPath.hpp"

#include "ImageImporter.hpp"
#include "asset/rTextureData.hpp"
#include "asset/rTextureFile.hpp"

#include "TextureAtlasImporter.hpp"
#include "asset/rTextureAtlasData.hpp"

#include <iostream>

namespace recondite { namespace tools {
	int Converter::Main(int argc, char** argv) {
		using namespace lambda_options::with_char;

		Options opts;

		opts.AddOption(Keyword("texture", "t"), [&](std::string inputfile) {
			this->ConvertImage(inputfile.c_str());
		});

		opts.AddOption(Keyword("texture_atlas", "ta"), [&](std::string manifest) {
			this->CreateTextureAtlas(manifest.c_str());
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

			rTextureFile textureFile;
			textureFile.Write(&m_fileSystem, outPath, textureData);
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

				rTextureFile textureFile;
				textureFile.Write(&m_fileSystem, textureOutPath, textureData);
			}
		}

		return error;
	}
}}