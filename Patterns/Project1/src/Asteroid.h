#pragma once

#include "GameObject.h"
#include "PhysicsEngine.h"
#include "GraphicsRender.h"
class Asteroid : public   GameObject
{
public:
	Asteroid();
	Asteroid(Model* model);
	~Asteroid();
	void LoadAsteroidModel();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	void SetId(const std::string& id);
	void SetActive(const bool& isactive);

	void AddPhysicsForthisObject();
private:

	GraphicsRender* renderer;
	Shader* shader;
	PhysicsEngine* engine;

	Model* copyModel;

	PhysicsObject* physicsObject = nullptr;

};

