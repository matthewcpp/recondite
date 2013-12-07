#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rContentManager* contentManager, rController* controller){
	m_controller = controller;
	m_contentManager = contentManager;

	m_pawn = new rPawn(NULL, "demo pawn", rVector3::ZeroVector);
}

ruiDemoController::~ruiDemoController(){
	delete m_pawn;
}

void ruiDemoController::Init(ruiOverlay* overlay){
	m_modelPicker = new ruiPicker(100, rPoint(25,10), rSize(250, 35));

	rArrayString models;
	m_contentManager->GetModelNames(models);
	m_modelPicker->SetOptions(models);

	m_modelPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnModelChange);

	m_animationPicker = new ruiPicker(101, rPoint(25,60), rSize(250, 35));

	overlay->AddWidget(new ruiDPad(m_controller->DPad(0), 999, rPoint(700, 300), rSize(300, 300)));
	overlay->AddWidget(m_modelPicker);
	overlay->AddWidget(m_animationPicker);

	if (models.size() > 0)
		SetActiveModel(models[0]);

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
	rMatrix4 transform;
	engine.renderer->RenderSkeleton(skeleton, transform, rColor::White);
}
