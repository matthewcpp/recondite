#include "Importer.hpp"

#include "rFileSystem.hpp"
#include "rPath.hpp"

#include "ImageImporter.hpp"
#include "asset/rTextureData.hpp"

#include "TextureAtlasImporter.hpp"
#include "asset/rTextureAtlasData.hpp"

#include "FontImporter.hpp"
#include "asset/rFontData.hpp"
#include "ModelImporter.hpp"

#include "xml/rXMLDocument.hpp"

#include <iostream>

namespace recondite { namespace tools {
	int Importer::Main(int argc, char** argv) {
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

		opts.AddOption(Keyword("model", "m"), [&](std::string inputFile){
			this->ConvertModel(inputFile.c_str());
		});

		opts.AddOption(Keyword("wmv", "w"), [&](std::string inputFile) {
			this->ImportWowModelViewer(inputFile.c_str());
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

	int Importer::ConvertImage(const rString& path) {
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

			auto outFile = m_fileSystem.OpenWriteFileRef(outPath);
			textureData.Write(*outFile);
			m_fileSystem.CloseWriteFileRef(outFile);
		}

		return error;
	}

	int Importer::CreateTextureAtlas(const rString& path) {
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

				auto atlasFile = m_fileSystem.OpenWriteFileRef(atlasOutPath);
				textureAtlasData.Write(*atlasFile);
				m_fileSystem.CloseWriteFileRef(atlasFile);

				auto outFile = m_fileSystem.OpenWriteFileRef(textureOutPath);
				textureData.Write(*outFile);
				m_fileSystem.CloseWriteFileRef(outFile);
			}
		}

		return error;
	}

	int Importer::ConvertFont(const rString& path){
		std::cout << "Generate Font from file: " << path << std::endl;

		import::FontImporter fontImporter;
		int error = fontImporter.ReadManifestFromPath(path);

		if (error){
			std::cout << "font file parse failed." << std::endl;
		}
		else{
			FontData fontData;
			error = fontImporter.GenerateFont(fontData);

			if (error){
				std::cout << "font generation failed." << std::endl;
				return 1;
			}
			else{
				rString outDir, outName;
				rPath::Split(path, &outDir, &outName, nullptr);

				rString fontOutPath = rPath::Assemble(outDir, outName, "rfnt");

				auto fontOutFile = m_fileSystem.OpenWriteFileRef(fontOutPath);
				fontData.Write(*fontOutFile);
				m_fileSystem.CloseWriteFileRef(fontOutFile);
			}
		}

		return error;
	}

	void OutputModelStats(const recondite::ModelData& modelData) {
		size_t faceCount = 0;
		for (size_t i = 0; i < modelData.GetTriangleMeshCount(); i++) {
			faceCount += modelData.GetTriangleMesh(i)->GetElementCount() / 3;
		}

		size_t lineCount = 0;
		for (size_t i = 0; i < modelData.GetLineMeshCount(); i++) {
			lineCount += modelData.GetLineMesh(i)->GetElementCount() / 2;
		}

		std::cout << "Model Stats:" << std::endl;
		std::cout << "\tVertices: " << modelData.GetGeometryData()->VertexCount() << std::endl;
		std::cout << "\tFaces: " << faceCount << std::endl;
		std::cout << "\tLines: " << lineCount << std::endl;
		std::cout << std::endl;

		std::cout << "\tMeshes: " << modelData.GetTriangleMeshCount() + modelData.GetLineMeshCount() << std::endl;
		std::cout << "\tTextures: " << modelData.GetNumTextures() << std::endl;
		std::cout << std::endl;

		recondite::Skeleton* skeleton = modelData.GetSkeleton();
		if (skeleton) {
			std::cout << "\tAnimations: " << skeleton->GetAnimationCount() << std::endl;
			std::cout << "\tBones: " << skeleton->GetBoneCount() << std::endl;
		}
	}

	int Importer::ImportWowModelViewer(const rString& path) {
		rString dirName, fileName, ext;
		rPath::Split(path, &dirName, &fileName, &ext);

		rXMLDocument xml;
		int error = xml.LoadFromFile(path);
		if (error) {
			std::cout << "Error parsing WMV input XML File." << std::endl;
			return 1;
		}

		rXMLElement* geometry = xml.GetRoot()->GetFirstChildNamed("geometry");
		rString geometryFile;
		geometry->GetText(geometryFile);
		geometryFile = rPath::Combine(dirName, geometryFile);

		import::ModelImporter modelImporter;
		import::ModelImporterOptions options;
		options.importAnimations = false;

		ModelData modelData;
		error = modelImporter.ImportModel(geometryFile, modelData, options);

		options.importAnimations = true;
		options.importMeshData = false;
		options.importSkeleton = false;

		rXMLElement* animations = xml.GetRoot()->GetFirstChildNamed("animations");
		for (size_t i = 0; i < animations->NumChildren(); i++) {
			rString fbxFile = rPath::Combine(dirName, animations->GetChild(i)->Text());
			int error = modelImporter.ImportModel(fbxFile, modelData, options);

			if (error) {
				std::cout << "Error reading animations from: " << fbxFile.c_str() << std::endl;
				return 1;
			}
			else {
				std::cout << "Read animation data from: " << fbxFile.c_str() << std::endl;
			}
		}

		OutputModelStats(modelData);

		rString modelOutPath = rPath::Assemble(dirName, fileName, "rmdl");
		auto modelOutFile = m_fileSystem.OpenWriteFileRef(modelOutPath);

		modelData.Write(*modelOutFile);
		m_fileSystem.CloseWriteFileRef(modelOutFile);

		return 0;
	}

	int Importer::ConvertModel(const rString& path){
		std:: cout << "Generate model from file: " << path << std::endl;

		import::ModelImporter modelImporter;
		import::ModelImporterOptions options;
		ModelData modelData;
		
		int error = modelImporter.ImportModel(path, modelData, options);

		if (!error){
			std::cout << "Model import successful." << std::endl;
			OutputModelStats(modelData);

			rString outDir, outName;
			rPath::Split(path, &outDir, &outName, nullptr);

			rString modelOutPath = rPath::Assemble(outDir, outName, "rmdl");
			auto modelOutFile = m_fileSystem.OpenWriteFileRef(modelOutPath);

			modelData.Write(*modelOutFile);

			m_fileSystem.CloseWriteFileRef(modelOutFile);
		}
		else{
			std::cout << "Model import failed." << std::endl;
		}
		return error;
	}
}}