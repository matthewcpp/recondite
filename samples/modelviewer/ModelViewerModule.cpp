#include "ModelViewerModule.hpp"
#include "ModelViewerController.hpp"
#include "ModelViewerCamera.hpp"

#include "rCamera.hpp"
#include "rProp.hpp"
#include "rPawn.hpp"


ModelViewerModule::ModelViewerModule(rEngine* engine)
{
	_engine = engine;
}

rViewport* ModelViewerModule::CreateView(Model* model, rEngine* engine) {
	rViewport* mainViewport = engine->viewports->CreateViewport("main");

	rAlignedBox3 boundingBox = model->GetBoundingBox();
	rVector3 center = boundingBox.Center();

	recondite::Camera* camera = new recondite::Camera();
	_demoCamera.reset(new ModelViewerCamera(camera, engine));
	mainViewport->SetCamera(camera);

	//set up decent clipping values
	rAlignedBox3 box = model->GetBoundingBox();
	
	float diagonal = box.min.Distance(box.max);
	_demoCamera->Reset(center, diagonal * 3, 0, 0);

	mainViewport->SetFarClip(diagonal * 10);

	rVector3 delta = (box.max - box.min) / 15.0;
	float nearClip = delta.x;
	nearClip = std::min(nearClip, delta.y);
	nearClip = std::min(nearClip, delta.z);
	mainViewport->SetNearClip(nearClip);

	return mainViewport;
}

bool ModelViewerModule::ParseArgs(const rArrayString& args, rString& file, rString& archive) {
	for (size_t i = 0; i < args.size(); i++) {
		if (args[i] == "--file") {
			file = args[i + 1];
		}

		else if (args[i] == "--archive") {
			archive = args[i + 1];
		}
	}

	return true;
}

void ModelViewerModule::Init(const rArrayString& args) {
	auto createControllerFunc = [&](const rString& name, rEngine* engine, ruiDocument* document) {
		return new ModelViewerController(_skeletonGeometry.get(), name, engine, document);
	};

	auto deleteControllerFunc = [](ruiController* controller) {
		delete controller;
	};

	_engine->ui->RegisterControllerClass("ModelViewerController", createControllerFunc, deleteControllerFunc);
	Model* model = nullptr;

	rString file, archive;
	ParseArgs(args, file, archive);

	if (!archive.empty()) {
		_engine->resources->OpenArchive(archive);
		model = _engine->content->Models()->LoadFromResource(file, "model");
	}
	else {
		auto fileSystemRef = _engine->filesystem->OpenReadFileRef(file);
		ModelData modelData;
		modelData.Read(*fileSystemRef);

		_engine->filesystem->CloseReadFileRef(fileSystemRef);

		model = _engine->content->Models()->LoadFromData(modelData, "model");
	}

	if (model->GetSkeleton()) {
		rPawn* pawn = new rPawn(model, "model", _engine);
		_skeletonGeometry.reset(new SkeletonGeometry(_engine, pawn));
		_engine->scene->AddActor(pawn);
	}
	else {
		rProp* prop = new rProp(model, "model", _engine);
		_engine->scene->AddActor(prop);
	}
	
	rViewport* mainViewport = CreateView(model, _engine);

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/modelviewer/modelviewer/modelviewer.xml", mainViewport);

}

void ModelViewerModule::AfterUpdateScene() {
	_demoCamera->Update();

	if (_skeletonGeometry)
		_skeletonGeometry->Update();
}

void ModelViewerModule::AfterRenderScene(rViewport* viewport) {
	if (_skeletonGeometry) {
		_skeletonGeometry->DrawSkeleton();
	}
}

void ModelViewerModule::BeforeRenderUi(rViewport* viewport) {
	if (_skeletonGeometry) {
		_skeletonGeometry->DrawLabels(viewport);
	}
}


