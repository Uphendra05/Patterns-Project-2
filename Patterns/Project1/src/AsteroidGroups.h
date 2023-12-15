#pragma once

#include "GameObject.h"

#include "GraphicsRender.h"

class AsteroidsGroups : public GameObject
{
public:
	AsteroidsGroups();
	AsteroidsGroups(Model* model);
	~AsteroidsGroups();

	void LoadAsteroidGroupModel();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	void SetId(const std::string& id);

	void SetActive(const bool& isActive);
private:

	GraphicsRender* renderer;
	Shader* shader;
};

