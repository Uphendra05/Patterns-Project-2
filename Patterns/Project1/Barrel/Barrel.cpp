#include "Barrel.h"
#include "../src/Singleton.h"

Barrel::Barrel()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);
}

Barrel::~Barrel()
{
}

void Barrel::Start()
{
	model = new Model("Models/Barrel/Barrel.obj");
	model->id = "BARREL";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, 0, 0));
	model->transform.SetScale(glm::vec3(2));
	render->AddModelsAndShader(model, defaultshader);
}

void Barrel::Update()
{
}

void Barrel::End()
{
}

Transform* Barrel::GetTransform()
{
	return &model->transform;
}
