#include "Bullet.h"
#include "../src/Singleton.h"
Bullet::Bullet()
{
	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();
	Singleton::GetInstance().AddGameObject(this);
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{

	model = new Model("Models/Bullet/Bullet.obj");
	model->id = "Bullet";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(30, 6.5, 12));
	model->transform.SetScale(glm::vec3(2));
	render->AddModelsAndShader(model, defaultshader);
}

void Bullet::Update()
{
}

void Bullet::End()
{
}

Transform* Bullet::GetTransform()
{
    return &model->transform;
}
