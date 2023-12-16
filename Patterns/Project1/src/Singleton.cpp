#include "Singleton.h"

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}

Singleton& Singleton::GetInstance()
{
	static Singleton instance;
	return instance;
}

void Singleton::SetRendererPhysicsEngineAndDefaultShader(GraphicsRender& render, Shader* defaultShader, PhysicsEngine& engine)
{
	this->renderer = &render;
	this->defaultShader = defaultShader;
	this->physicsEngine = &engine;

}

void Singleton::SetCamera(Camera& camera)
{
	this->camera = &camera;
}

GraphicsRender* Singleton::GetRenderer()
{
	return renderer;
}

Shader* Singleton::GetDefaultShader()
{
	return defaultShader;
}

PhysicsEngine* Singleton::GetPhysicsEngine()
{
	return physicsEngine;
}

Camera* Singleton::GetCamera()
{
	return camera;
}

Model* Singleton::GetDefaultCube()
{
	return defaultCube;
}

Model* Singleton::GetDefaultSphere()
{
	return defaultSphere;
}

std::vector<GameObject*> Singleton::GetGameObjectList()
{
	return GameObejctsList;
}

void Singleton::AddGameObject(GameObject* gameObject)
{
	GameObejctsList.push_back(gameObject);
}

void Singleton::SetDefaultSphere(Model* sphere)
{
	this->defaultSphere = sphere;
}

void Singleton::SetDefaultCube(Model* cube)
{
	this->defaultCube = cube;
}
