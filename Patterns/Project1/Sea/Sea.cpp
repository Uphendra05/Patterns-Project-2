#include "Sea.h"
#include "../src/Singleton.h"

Sea::Sea()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);

}

Sea::~Sea()
{
}

void Sea::Start()
{

	model = new Model("Models/Sea/Sea.obj");
	model->id = "Sea";
	model->meshes[0]->SetTileable(true);
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, -2, 0));
	model->transform.SetScale(glm::vec3(1000));
	render->AddModelsAndShader(model, defaultshader);
	

}

void Sea::Update()
{

}

void Sea::End()
{
}

Transform* Sea::GetTransform()
{
	return &model->transform;
}
