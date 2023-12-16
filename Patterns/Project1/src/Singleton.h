#pragma once
#include "GraphicsRender.h"
#include "PhysicsEngine.h"
#include "GameObject.h"

class Singleton
{
public:
	Singleton();
	~Singleton();

	static Singleton& GetInstance();

	void SetRendererPhysicsEngineAndDefaultShader(GraphicsRender& render, Shader* defaultShader, PhysicsEngine& engine );
	
	GraphicsRender* GetRenderer();

	Shader* GetDefaultShader();

	PhysicsEngine* GetPhysicsEngine();

	std::vector<GameObject*> GetGameObjectList();
	void AddGameObject(GameObject* gameObject);

private:

	static Singleton instance;

	GraphicsRender* renderer;
	PhysicsEngine* physicsEngine;
	Shader* defaultShader;
	std::vector<GameObject*> GameObejctsList;

};

