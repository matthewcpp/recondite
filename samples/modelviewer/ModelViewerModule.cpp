#include "ModelViewerModule.hpp"
#include "ModelViewerController.hpp"
#include "rDemoCamera.hpp"

#include "rCamera.hpp"
#include "rProp.hpp"
#include "rPawn.hpp"


ModelViewerModule::ModelViewerModule(rEngine* engine)
	:rModule("Model Viewer Sample") 
{
	_engine = engine;
}

rViewport* CreateView(Model* model, rEngine* engine) {
	rViewport* mainViewport = engine->component->CreateViewport("main");

	rAlignedBox3 boundingBox = model->GetBoundingBox();
	rVector3 center = boundingBox.Center();

	rDemoCamera* camera = new rDemoCamera("main_camera", engine);
	engine->scene->AddActor(camera);
	mainViewport->SetCamera(camera);

	//set up decent clipping values
	rAlignedBox3 box = model->GetBoundingBox();
	
	float diagonal = box.min.Distance(box.max);
	camera->Reset(center, diagonal * 3, 0, 0);

	mainViewport->SetFarClip(diagonal * 10);

	rVector3 delta = (box.max - box.min) / 15.0;
	float nearClip = delta.x;
	nearClip = std::min(nearClip, delta.y);
	nearClip = std::min(nearClip, delta.z);
	mainViewport->SetNearClip(nearClip);

	return mainViewport;
}

void ModelViewerModule::Init(const rArrayString& args) {
	auto createControllerFunc = [&](const rString& name, rEngine* engine, ruiDocument* document) {
		return new ModelViewerController(&settings, name, engine, document);
	};

	auto deleteControllerFunc = [](ruiController* controller) {
		delete controller;
	};

	_engine->ui->RegisterControllerClass("ModelViewerController", createControllerFunc, deleteControllerFunc);

	auto fileSystemRed = _engine->content->FileSystem()->GetReadFileRef(args[0]);
	ModelData modelData;
	modelData.Read(*fileSystemRed);

	CreateSkeletonGeometry(modelData);

	Model* model =_engine->content->Models()->LoadFromData(modelData, "model");
	
	rActor3* actor = nullptr;
	if (model->GetSkeleton()) {
		actor = new rPawn(model, "model", _engine);
		settings.animatedModel = true;
	}
	else {
		actor = new rProp(model, "model", _engine);
		settings.animatedModel = false;
	}
	_engine->scene->AddActor(actor);

	rViewport* mainViewport = CreateView(model, _engine);

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/modelviewer/modelviewer/modelviewer.xml", mainViewport);

}

void ModelViewerModule::CreateSkeletonGeometry(recondite::ModelData& modelData) {
	recondite::Skeleton* skeleton = modelData.GetSkeleton();

	if (skeleton) {
		skeletonBuffer.Reset(rGeometryType::Lines, 3, false);

		recondite::MaterialData* skeletonMaterial = modelData.CreateMaterial();
		skeletonMaterial->diffuseColor = rColor::Green;

		std::vector<rVector3> points;

		size_t boneCount = skeleton->GetBoneCount();
		for (size_t i = 0; i < boneCount; i++) {
			recondite::Bone* bone = skeleton->GetBone(i);

			rVector3 bonePos = skeleton->GetGlobalTransform(bone).GetTranslate();
			boneLabelPoints[bone->name] = bonePos;

			if (!bone->IsRoot()) {
				recondite::Bone* parent = skeleton->GetBone(bone->parentId);

				rVector3 parentPos = skeleton->GetGlobalTransform(parent).GetTranslate();

				skeletonBuffer.PushVertex(bonePos);
				skeletonBuffer.PushVertex(parentPos);


				size_t indexCount = skeletonBuffer.IndexCount();
				skeletonBuffer.PushIndex(indexCount, indexCount + 1);
			}
		}
	}
}

void ModelViewerModule::LoadScene(const rString& sceneName) {

}

void ModelViewerModule::DeleteActor(rActor3* actor) {
	delete actor;
}

void ModelViewerModule::AfterRenderScene(rViewport* viewport) {
	if (skeletonBuffer.VertexCount() > 0 && settings.renderSkeleton) {
		_engine->renderer->EnableDepthTesting(false);
		_engine->renderer->RenderImmediateLines(skeletonBuffer, settings.skeletonLineColor);
		_engine->renderer->EnableDepthTesting(true);
	}
}

void ModelViewerModule::BeforeRenderUi(rViewport* viewport) {
	if (settings.renderSkeleton && settings.renderBoneNames) {
		rRect screenRect = viewport->GetScreenRect();

		rMatrix4 viewMatrix, projectionMatrix;
		viewport->GetViewMatrix(viewMatrix);
		viewport->GetProjectionMatrix(projectionMatrix);

		rSpriteBatch* sb = _engine->renderer->SpriteBatch();

		for (auto& boneLabel : boneLabelPoints) {
			rVector2 projectedPoint;
			rMatrixUtil::Project(boneLabel.second, viewMatrix, projectionMatrix, screenRect, projectedPoint);
			projectedPoint.y = float(screenRect.height) - projectedPoint.y;

			sb->RenderString(boneLabel.first, _engine->content->Fonts()->SystemDefault(), rPoint(projectedPoint.x, projectedPoint.y), settings.skeletonTextColor);
		}
	}
}

