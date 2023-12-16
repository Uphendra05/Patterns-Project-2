#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"
#include "LuaManager.h"
#include "LuaHandler.h"
#include "GameObject.h"
class Ball  :  public GameObject
{
public:
	Ball();
	~Ball();

	
	PhysicsObject* shipPhysics;

	void LoadModel();

	//void Update(float deltaTime);

	Transform* GetTransform() override;

	LuaHandler* m_LuaHandler;

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	glm::vec3 Direction = glm::vec3(0, 0, 0);
	float speed = 20;
};



