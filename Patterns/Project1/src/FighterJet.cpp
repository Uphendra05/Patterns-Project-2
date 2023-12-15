
#include "FighterJet.h"
#include "Singleton.h"

FighterJet::FighterJet()
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();
	engine = Singleton::GetInstance().GetPhysicsEngine();

	LoadFighterModel();
}

FighterJet::FighterJet(Model* copyModel)
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = Singleton::GetInstance().GetDefaultShader();
	engine = Singleton::GetInstance().GetPhysicsEngine();

	this->copyModel = copyModel;

	LoadFighterModel();
	SetActive(false);
}

FighterJet::FighterJet(Model* copyModel, Shader* DestroyShader)
{
	renderer = Singleton::GetInstance().GetRenderer();
	shader = DestroyShader;
	engine = Singleton::GetInstance().GetPhysicsEngine();

	this->copyModel = copyModel;

	LoadFighterModel();
	SetActive(false);
}

FighterJet::~FighterJet()
{
}

void FighterJet::LoadFighterModel()
{
	if (copyModel == nullptr)
	{
		copyModel = new Model("Models/FighterJet/FighterJet.ply");
	}

	model = new Model(*copyModel);
	//model = new Model("Models/Asteroids/AsteroidGroup.ply");
	model->id = "FIGHTER";
	SetGameObjectId(model->id);

	renderer->AddModelsAndShader(model, shader);
}

void FighterJet::SetPosition(const glm::vec3& position)
{
	model->transform.SetPosition(position);
}

void FighterJet::SetRotation(const glm::vec3& rotation)
{
	model->transform.SetRotation(rotation);

}

void FighterJet::SetScale(const glm::vec3& scale)
{
	model->transform.SetScale(scale);

}

void FighterJet::AddPhysicsForthisObject()
{
	fighterPhysics = new PhysicsObject(model);
	fighterPhysics->Initialize(AABB, true, DYNAMIC);

	fighterPhysics->gravityValue = 0;

	fighterPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id =="ASTEROID5" || other->model->id == "BOX_TRIGGER")
			{
				ISFIGHTERCOLLIDED = true;

				shader->Bind();
				shader->setFloat("explosionOffset", explosionOffset);
				explosionOffset += 0.5f;
			}
			
		});

	engine->AddPhysicsObjects(fighterPhysics);


}

void FighterJet::Update(float deltaTime)
{
	if (ISFIGHTERCOLLIDED)
	{
	

	}
}

void FighterJet::SetId(const std::string& id)
{
	model->id = id;
	SetGameObjectId(id);
}

void FighterJet::SetActive(const bool& isactive)
{
	model->isVisible = isactive;
}
