#pragma once
#include "GraphicsRender.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "Camera.h"
class Singleton
{
public:
	Singleton();
	~Singleton();

	static Singleton& GetInstance();

	void SetRendererPhysicsEngineAndDefaultShader(GraphicsRender& render, Shader* defaultShader, PhysicsEngine& engine );
	void SetCamera(Camera& camera);

	GraphicsRender* GetRenderer();

	Shader* GetDefaultShader();

	PhysicsEngine* GetPhysicsEngine();

	Camera* GetCamera();

	std::vector<GameObject*> GetGameObjectList();
	void AddGameObject(GameObject* gameObject);

private:

	static Singleton instance;

	GraphicsRender* renderer;
	PhysicsEngine* physicsEngine;
	Shader* defaultShader;
	Camera* camera;

	std::vector<GameObject*> GameObejctsList;

};

