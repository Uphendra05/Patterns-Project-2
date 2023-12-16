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

void WaterShipEnemy::AddPhysics()
{
	shipPhysics = new PhysicsObject(model);

	shipPhysics->Initialize(AABB, false, STATIC);

	shipPhysics->gravityValue = 0;

	engine->AddPhysicsObjects(shipPhysics);


}

void WaterShipEnemy::Start()
{

	model = new Model("Models/Ship/Ship2.obj");
	model->id = "ENEMYSHIP";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(30,-2.5,12));
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
