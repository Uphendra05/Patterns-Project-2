#pragma once

#include "GameObject.h"
#include "GraphicsRender.h"
#include "PhysicsEngine.h"

extern bool ISFIGHTERCOLLIDED;
class FighterJet : public GameObject
{
public:
	FighterJet();
	FighterJet(Model* copyModel);
	FighterJet(Model* copyModel, Shader* DestroyShader);
	~FighterJet();

	void LoadFighterModel();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	void  AddPhysicsForthisObject();
	void Update(float deltaTime);
	

	void SetId(const std::string& id);
	void SetActive(const bool& isactive);

private:

	GraphicsRender* renderer;

	Shader* shader;

	PhysicsEngine* engine;

	Model* copyModel = nullptr;

	PhysicsObject* fighterPhysics = nullptr;

	float timeStep = 2;
	float explosionOffset =0;

};
