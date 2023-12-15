#include "Asteroid.h"
#include "Singleton.h"
Asteroid::Asteroid()
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();
	engine = Singleton::GetInstance().GetPhysicsEngine();

	LoadAsteroidModel();

	SetActive(false);
}

Asteroid::Asteroid(Model* model)
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();
	engine = Singleton::GetInstance().GetPhysicsEngine();

	copyModel = model;

	LoadAsteroidModel();
	SetActive(false);
}

Asteroid::~Asteroid()
{
}

void Asteroid::LoadAsteroidModel()
{
	if (copyModel == nullptr)
	{
		copyModel = new Model("Models/Asteroids/Asteroid_1.ply");
	}

	model = new Model(*copyModel);
	//model = new Model("Models/Asteroids/AsteroidGroup.ply");
	model->id = "ASTEROID";
	SetGameObjectId(model->id);

	renderer->AddModelsAndShader(model, shader);
}

void Asteroid::SetPosition(const glm::vec3& position)
{
	model->transform.SetPosition(position);
}

void Asteroid::SetRotation(const glm::vec3& rotation)
{
	model->transform.SetRotation(rotation);
}

void Asteroid::SetScale(const glm::vec3& scale)
{
	model->transform.SetScale(scale);
}

void Asteroid::SetId(const std::string& id)
{
	model->id = id;
	SetGameObjectId(id);
}

void Asteroid::SetActive(const bool& isactive)
{
	model->isVisible = isactive;
}

void Asteroid::AddPhysicsForthisObject()
{
	physicsObject = new PhysicsObject(model);
	physicsObject->Initialize(AABB, false, STATIC);

	physicsObject->gravityValue = 0;

	engine->AddPhysicsObjects(physicsObject);


}
