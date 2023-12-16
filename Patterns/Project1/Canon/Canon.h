#pragma once
#include "../src/PhysicsEngine.h"
#include "../src/GraphicsRender.h"
#include "../src/LuaManager.h"
#include "../src/LuaHandler.h"
#include "../src/GameObject.h"
class Canon : public GameObject
{



public:

	Canon();
	~Canon();

	void Start();
	void Update();
	void End();

	PhysicsObject* ballPhysics;
	Transform* GetTransform() override;

private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	glm::vec3 Direction = glm::vec3(0, 0, 0);
	float speed = 20;
};

