#include "Canon.h"
#include "../src/Singleton.h"

Canon::Canon()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);
	Start();

}

Canon::~Canon()
{
}

void Canon::Start()
{

	model = new Model("Models/Box/DefaultCube.fbx");
	model->id = "CANON";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, 5, 0));
	model->transform.SetScale(glm::vec3(1));
	render->AddModelsAndShader(model, defaultshader);

}

void Canon::Update()
{
}

void Canon::End()
{
}

Transform* Canon::GetTransform()
{
	return  &model->transform;
}
