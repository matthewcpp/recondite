#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rContentManager* contentManager, rPawn* pawn){
	m_contentManager = contentManager;
	m_pawn = pawn;
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

	overlay->AddWidget(m_modelPicker);
	overlay->AddWidget(m_animationPicker);

	if (models.size() > 0)
		SetActiveModel(models[0]);

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

	m_pawn->SetModel(model);
	model->Skeleton()->GetAnimationNames(animationNames);

	m_animationPicker->SetOptions(animationNames);
}

void ruiDemoController::OnUpdate(rEngine& engine){
	m_pawn->Update(engine);
}

void ruiDemoController::OnDraw(rEngine& engine){
	m_pawn->Draw(engine);

	rSkeleton* skeleton = m_pawn->Model()->Skeleton();

	rAnimationPlayer* animationPlayer = m_pawn->AnimationPlayer();
	const rMatrix4Vector& transformData = animationPlayer->GetTransformData();

	engine.renderer->RenderSkeleton(skeleton, transformData, rColor::White);
}
