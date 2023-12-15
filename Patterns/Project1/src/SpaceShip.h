#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"
#include "LuaManager.h"
#include "LuaHandler.h"
#include "GameObject.h"

class SpaceShip :public GameObject
{
public:
	SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera);
	SpaceShip();
	SpaceShip(const std::string id);
	~SpaceShip();


	PhysicsObject* SpaceShipPhysics;

	void LoadModel();

	void Update(float deltaTime);
	
	LuaHandler* m_LuaHandler;

	void SetActive(const bool& isactive);

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;

	glm::vec3 Direction = glm::vec3(0, 0, 0);
	glm::vec3 cameraOffset = glm::vec3(0, -2, 3.5f);
	float speed = 20;

	std::string id;
};

