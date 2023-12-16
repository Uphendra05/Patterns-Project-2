#pragma once

#include "../src/PhysicsEngine.h"
#include "../src/GraphicsRender.h"
#include "../src/LuaManager.h"
#include "../src/LuaHandler.h"
#include "../src/GameObject.h"


class SeaGul : public GameObject
{



public:

	SeaGul();
	SeaGul(Model* model);
	~SeaGul();

	void Start();
	void Update();
	void End();

	PhysicsObject* shipPhysics;
	Transform* GetTransform() override;
	LuaHandler* m_LuaHandler;
	Model* copyModel;
private:


	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	glm::vec3 Direction = glm::vec3(0, 0, 0);
	float speed = 20;

};

