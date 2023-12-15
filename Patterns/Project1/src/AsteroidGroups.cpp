#include "AsteroidGroups.h"
#include "Singleton.h"

AsteroidsGroups::AsteroidsGroups()
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();

	LoadAsteroidGroupModel();

	SetActive(false);
}

AsteroidsGroups::AsteroidsGroups(Model* model)
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();

	copyModel = model;

	LoadAsteroidGroupModel();

	SetActive(false);
}

AsteroidsGroups::~AsteroidsGroups()
{
}

void AsteroidsGroups::LoadAsteroidGroupModel()
{
	if (copyModel == nullptr)
	{
		copyModel = new Model("Models/Asteroids/AsteroidGroup.ply");
	}

	model = new Model(*copyModel);
	//model = new Model("Models/Asteroids/AsteroidGroup.ply");
	model->id = "ASTEROIDGROUPS";
	SetGameObjectId(model->id);

	renderer->AddModelsAndShader(model, shader);
}

void AsteroidsGroups::SetPosition(const glm::vec3& position)
{
	model->transform.SetPosition(position);
}

void AsteroidsGroups::SetRotation(const glm::vec3& rotation)
{
	model->transform.SetRotation(rotation);
}

void AsteroidsGroups::SetScale(const glm::vec3& scale)
{
	model->transform.SetScale(scale);
}

void AsteroidsGroups::SetId(const std::string& id)
{
	model->id = id;
	SetGameObjectId(id);
}

void AsteroidsGroups::SetActive(const bool& isActive)
{
	model->isVisible = isActive;
}
