#include "SeaGul.h"
#include "../src/Singleton.h"

SeaGul::SeaGul()
{


	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);
}

SeaGul::SeaGul(Model* model)
{
	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);

	copyModel = model;
}

SeaGul::~SeaGul()
{
}

void SeaGul::Start()
{
	if (copyModel ==nullptr)
	{
		model = new Model("Models/Seagull/Seagul.obj");
	}
	else
	{
		model = new Model(*copyModel);
	}
	//model = new Model("Models/Seagull/Seagul.obj");
	model->id = "Seagull";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, 10, 0));
	model->transform.SetRotation(glm::vec3(0, 90, 0));
	model->transform.SetScale(glm::vec3(.05));
	render->AddModelsAndShader(model, defaultshader);



}

void SeaGul::Update()
{
}

void SeaGul::End()
{
}

Transform* SeaGul::GetTransform()
{
    return &model->transform;
}
