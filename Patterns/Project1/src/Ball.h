#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"
#include "LuaManager.h"
#include "LuaHandler.h"

class Ball
{
public:
	Ball(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~Ball();

	Model* model;
	PhysicsObject* ballPhysics;

	void LoadModel();

	void Update(float deltaTime);

	LuaHandler* m_LuaHandler;

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	glm::vec3 Direction = glm::vec3(0, 0, 0);
	float speed = 20;
};



