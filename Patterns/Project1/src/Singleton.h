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
	void AddGameObject(GameObject* gameObject);
	void SetDefaultSphere(Model* sphere);
	void SetDefaultCube(Model* cube);

	GraphicsRender* GetRenderer();
	Shader* GetDefaultShader();
	PhysicsEngine* GetPhysicsEngine();
	Camera* GetCamera();

	Model* GetDefaultCube();
	Model* GetDefaultSphere();

	std::vector<GameObject*> GetGameObjectList();




private:

	static Singleton instance;

	GraphicsRender* renderer;
	PhysicsEngine* physicsEngine;
	Shader* defaultShader;
	Camera* camera;

	Model* defaultSphere;
	Model* defaultCube;


	std::vector<GameObject*> GameObejctsList;

};

