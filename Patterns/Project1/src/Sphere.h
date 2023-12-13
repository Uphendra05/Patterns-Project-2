#pragma once
#include "GraphicsRender.h"

#include "GameObject.h"
#include "LuaHandler.h"
class SphereTest : public GameObject
{
public:
	SphereTest();
	~SphereTest();

	void LoadModel();
private:

	GraphicsRender* renderer;
	Shader* shader;
	
	LuaHandler* luaHandler;

};
