#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rContentManager* contentManager, rPawn* pawn, rDemoCamera* camera){
	m_contentManager = contentManager;
	m_pawn = pawn;
	m_camera = camera;

}

ruiDemoController::~ruiDemoController(){
	delete m_pawn;
}

void ruiDemoController::Init(ruiOverlay* overlay){
	rArrayString models;
	m_contentManager->GetModelNames(models);

	m_modelPicker = new ruiPicker(models, 100, rPoint(25,10), rSize(250, 35));

	m_modelPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnModelChange);

	m_animationPicker = new ruiPicker(101, rPoint(25,60), rSize(250, 35));
	m_animationPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnAnimationChange);

	m_animationTime = new ruiText("0.0", 102, rPoint(25, 110), rSize(100, 35));

	ruiButton* playButton = new ruiButton("Play", 103, rPoint(25, 160), rSize(100, 35));
	ruiButton* pauseButton = new ruiButton("Pause", 104, rPoint(135, 160), rSize(100, 35));
	ruiButton* stopButton = new ruiButton("Stop", 105, rPoint(245, 160), rSize(100, 35));

	playButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationPlay);
	pauseButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationPause);
	stopButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationStop);

	m_progressSlider = new ruiSlider(106, rPoint(145, 110), rSize(130, 35));

	overlay->AddWidget(m_modelPicker);
	overlay->AddWidget(m_animationPicker);
	overlay->AddWidget(m_animationTime);
	overlay->AddWidget(playButton);
	overlay->AddWidget(pauseButton);
	overlay->AddWidget(stopButton);
	overlay->AddWidget(m_progressSlider);

	if (models.size() > 0)
		SetActiveModel(models[0]);

}

void ruiDemoController::OnAnimationPlay(ruiWidget* widget){
	m_pawn->AnimationPlayer()->Play();
}

void ruiDemoController::OnAnimationPause(ruiWidget* widget){
	m_pawn->AnimationPlayer()->Pause();
}

void ruiDemoController::OnAnimationStop(ruiWidget* widget){
	m_pawn->AnimationPlayer()->Stop();
}

void ruiDemoController::OnAnimationChange(ruiWidget* widget){
	ruiPicker* animPicker = (ruiPicker*)widget;

	m_pawn->AnimationPlayer()->PlayAnimation(animPicker->SelectionText());
}

void ruiDemoController::OnModelChange(ruiWidget* widget){
	ruiPicker* modelPicker = (ruiPicker*)widget;

	SetActiveModel(modelPicker->SelectionText());
}

void ruiDemoController::SetActiveModel(const rString& name){
	rArrayString animationNames;
	rModel* model = m_contentManager->GetModelAsset(name);
	rAlignedBox3 boundingBox = model->BoundingBox();
	float radius = rMath::Max3(boundingBox.Width(), boundingBox.Height(), boundingBox.Depth()) * 2;

	m_pawn->SetModel(model);
	model->Skeleton()->GetAnimationNames(animationNames);
	m_pawn->AnimationPlayer()->SetAnimation(animationNames[0]);

	m_animationPicker->SetOptions(animationNames);

	m_camera->Reset(boundingBox.Center(), radius, 0, 0);

	SetupImmediateBuffer(name);
}

void ruiDemoController::OnUpdate(rEngine& engine){
	rAnimationPlayer* animationPlayer = m_pawn->AnimationPlayer();
	const rAnimation* anim = animationPlayer->CurrentAnimation();
	float animationTime = animationPlayer->AnimationTime();


	if (anim){
		float progress = animationTime / anim->Duration();
		m_progressSlider->SetValue(int(progress * 100));
	}
	else{
		m_progressSlider->SetValue(0);
	}

	std::ostringstream stream;
	stream << animationTime;

	m_animationTime->SetText(stream.str());
}

void ruiDemoController::OnDraw(rEngine& engine){
	RenderAnimated(engine);

	//m_pawn->Draw(engine);
	/*
	rSkeleton* skeleton = m_pawn->Model()->Skeleton();

	rAnimationPlayer* animationPlayer = m_pawn->AnimationPlayer();
	const rMatrix4Vector& transformData = animationPlayer->GetTransformData();

	engine.renderer->RenderSkeleton(skeleton, transformData, rColor::White, rColor::Green, 5.0f);
	*/
}

void ruiDemoController::SetupImmediateBuffer(const rString name){
	rString file = "content/models/" +name + "/" + name + ".rgeo";
	rGeometryDataReader reader;
	reader.ReadFromFile(file, m_geometryData);

	for (rImmediateBufferMap::iterator it = m_buffers.begin(); it != m_buffers.end(); ++it)
		delete it->second;
	
	m_buffers.clear();

	rArrayString elementBuffers;
	m_geometryData.GetElementBufferNames(elementBuffers);

	for (size_t i = 0; i < elementBuffers.size(); i++){
		rElementBufferData* bufferData = m_geometryData.GetElementBuffer(elementBuffers[i]);

		rImmediateBuffer* buffer = new rImmediateBuffer(rGEOMETRY_TRIANGLES, 3, true);
		buffer->Allocate(m_geometryData.VertexCount());
		buffer->SetIndexBuffer(bufferData->GetElementData(), bufferData->ElementCount());

		m_buffers[elementBuffers[i]] = buffer;
	}
}

void ruiDemoController::RenderAnimated(rEngine& engine){
	rAnimationPlayer* animationPlayer = m_pawn->AnimationPlayer();
	rModel* model = engine.content->GetModelAsset(m_modelPicker->SelectionText());

	const rMatrix4Vector& transformData = animationPlayer->GetTransformData();
	const rVertexBoneLinkMap& boneLinks = m_geometryData.VertexBoneLinks();

	rVector3 position;
	rVector2 texCoord;
	rMatrix4 mat;
	int count;

	for (size_t i =0; i < m_geometryData.VertexCount(); i++){
		m_geometryData.GetVertex(i, &position, &texCoord, NULL);

		rVertexBoneLinkResult result = boneLinks.equal_range(i);

		count = 0;
		for (rVertexBoneLinkMap::const_iterator it = result.first; it != result.second; ++it){
			const rVertexBoneLink& link = it->second;
			if (count)
				mat += transformData[link.boneIndex] * link.weight;
			else 
				mat = transformData[link.boneIndex] * link.weight;

			count ++;
		}

		mat.TransformVector3(position);

		rImmediateBufferMap::iterator end = m_buffers.end();
		for (rImmediateBufferMap::iterator it = m_buffers.begin(); it != end; ++it){
			it->second->SetVertex(i, position, texCoord);
		}
	}

	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		if (m_buffers.count(mesh->buffer)){
			engine.renderer->RenderBuffer(*m_buffers[mesh->buffer], mesh->material);
		}
	}
}
