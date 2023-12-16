#include "SharkTwo.h"
#include "../src/Singleton.h"
SharkTwo::SharkTwo()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);


}

SharkTwo::~SharkTwo()
{
}

void SharkTwo::Start()
{


	model = new Model("Models/Shark/Shark.obj");
	model->id = "SHARK2";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(0, -25, -80));
	model->transform.SetScale(glm::vec3(3, 3, 3));
	render->AddModelsAndShader(model, defaultshader);
}

void SharkTwo::Update()
{
}

void SharkTwo::End()
{
}

Transform* SharkTwo::GetTransform()
{
	return &model->transform;
}
