#include "WaterShipEnemy.h"
#include "../src/Singleton.h"


WaterShipEnemy::WaterShipEnemy()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);
}

WaterShipEnemy::~WaterShipEnemy()
{
}

void WaterShipEnemy::Start()
{

	model = new Model("Models/Ship/Ship2.obj");
	model->id = "ENEMYSHIP";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(10,-2.5,12));
	render->AddModelsAndShader(model, defaultshader);
}

void WaterShipEnemy::Update()
{
}

void WaterShipEnemy::End()
{
}

Transform* WaterShipEnemy::GetTransform()
{
	return &model->transform;
}
