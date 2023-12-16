#include "Shark.h"
#include "../src/Singleton.h"

Shark::Shark()
{
	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);



}

Shark::~Shark()
{
}

void Shark::Start()
{

	model = new Model("Models/Shark/Shark.obj");
	model->id = "SHARK";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, -25, -120));
	model->transform.SetScale(glm::vec3(12,10,12));
	render->AddModelsAndShader(model, defaultshader);
}

void Shark::Update()
{
}

void Shark::End()
{
}

Transform* Shark::GetTransform()
{
	return &model->transform;
}
