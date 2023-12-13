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
