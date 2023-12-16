#include "WaterShip.h"
#include "../src/Singleton.h"

WaterShip::WaterShip()
{

	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);


}

WaterShip::~WaterShip()
{
}

void WaterShip::Start()
{

	model = new Model("Models/Ship/Ship.obj");
	model->id = "SHIP";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(-30, -2.5, -12));
	model->transform.SetRotation(glm::vec3(0,180,0));
	render->AddModelsAndShader(model, defaultshader);


}

void WaterShip::Update()
{
}

void WaterShip::End()
{
}

Transform* WaterShip::GetTransform()
{
	return &model->transform;
}

void WaterShip::AddPhysics()
{
	shipPhysics = new PhysicsObject(model);

	shipPhysics->Initialize(AABB, false, STATIC);

	shipPhysics->gravityValue = 0;

	engine->AddPhysicsObjects(shipPhysics);


}
