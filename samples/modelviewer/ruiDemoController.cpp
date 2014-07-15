#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rContentManager* contentManager, rDemoCamera* camera){
	m_contentManager = contentManager;
	m_pawn = NULL;
	m_camera = camera;

}

void ruiDemoController::Init(ruiOverlay* overlay, rEngine* engine){
	rArrayString models;
	m_contentManager->GetModelNames(models);

	m_modelPicker = new ruiPicker(models, "100", engine, rPoint(25, 10), rSize(250, 35));

	m_modelPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnModelChange);

	m_animationPicker = new ruiPicker("101", engine, rPoint(25, 60), rSize(250, 35));
	m_animationPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnAnimationChange);

	m_animationTime = new ruiText("0.0", "102", engine, rPoint(25, 110), rSize(100, 35));

	ruiButton* playButton = new ruiButton("Play", "103", engine, rPoint(25, 160), rSize(100, 35));
	ruiButton* pauseButton = new ruiButton("Pause", "104",  engine, rPoint(135, 160), rSize(100, 35));
	ruiButton* stopButton = new ruiButton("Stop", "105", engine, rPoint(245, 160), rSize(100, 35));

	playButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationPlay);
	pauseButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationPause);
	stopButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnAnimationStop);

	m_progressSlider = new ruiSlider("106", engine, rPoint(145, 110), rSize(130, 35));

	overlay->AddWidget(m_modelPicker);
	overlay->AddWidget(m_animationPicker);
	overlay->AddWidget(m_animationTime);
	overlay->AddWidget(playButton);
	overlay->AddWidget(pauseButton);
	overlay->AddWidget(stopButton);
	overlay->AddWidget(m_progressSlider);
	overlay->AddWidget(new ruiTextBox("107", engine, rPoint(25, 200), rSize(100, 35)));
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
	rSkeleton* skeleton = model->Skeleton();

	if (skeleton){
		skeleton->GetAnimationNames(animationNames);

		if (animationNames.size() > 0){
			m_pawn->AnimationPlayer()->SetAnimation(animationNames[0]);
			m_animationPicker->SetOptions(animationNames);
		}
		else{
			m_animationPicker->Clear();
		}
	}
	else{
		m_animationPicker->Clear();
	}
	

	m_camera->Reset(boundingBox.Center(), radius, 0, 0);
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

	m_animationTime->SetText(stream.str().c_str());
}

void ruiDemoController::SetPawn(rDemoPawn* pawn){
	m_pawn = pawn;
}