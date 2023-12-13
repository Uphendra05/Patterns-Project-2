#pragma once
#include "GraphicsRender.h"
#include "PhysicsEngine.h"

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


private:

	static Singleton instance;

	GraphicsRender* renderer;
	PhysicsEngine* physicsEngine;
	Shader* defaultShader;

};

