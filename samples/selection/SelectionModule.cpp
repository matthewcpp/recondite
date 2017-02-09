#include "SelectionModule.hpp"

#include "primitive/rPrimitiveBox.hpp"
#include "stream/rOStringStream.hpp"

#include <random>

SelectionModule::SelectionModule(rEngine* engine)
	:recondite::Module(engine, "Selection Example")
{
	_engine = engine;
}

void SelectionModule::Init(const rArrayString& args) {
	rViewport* viewport = _engine->viewports->CreateViewport("main");
	Camera* camera = new recondite::Camera();
	camera->SetPosition(0.0f, 18.0f, 35.0f);
	camera->SetTarget(rVector3::ZeroVector);
	camera->SetUp(rVector3::UpVector);

	viewport->SetCamera(camera);
	
	CreatePrimitives();
}

void SelectionModule::CreatePrimitives() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint32_t> randomByte(0, 255);

	rVector3 position(-10.0f, 0.0f, -10.0f);
	rColor color;

	for (int x = 0; x < 5; x++) {
		position.z = -10.0f;

		for (int z = 0; z < 5; z++) {
			color.Set(randomByte(rng), randomByte(rng), randomByte(rng), 255);

			rPrimitiveBox* box = new rPrimitiveBox(_engine->scene->GetDefaultActorId("box"), _engine);
			box->SetPosition(position);
			box->SetFaceColor(color);

			_engine->scene->AddActor(box);

			position.z += 5.0f;
		}

		position.x += 5.0f;
	}
}