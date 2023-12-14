
#include "Sphere.h"
#include "Singleton.h"

SphereTest::SphereTest()
{
	this->renderer = Singleton::GetInstance().GetRenderer();
	this->shader = Singleton::GetInstance().GetDefaultShader();

	
	LoadModel();
}

SphereTest::~SphereTest()
{

}

void SphereTest::LoadModel()
{
	model = new Model("Models/Box/DefaultCube.fbx");
	model->id = "SphereTest";
	SetGameObjectId(model->id);


	model->transform.SetPosition(glm::vec3(0, 0, 0));


	renderer->AddModelsAndShader(model, shader);

	luaHandler = new LuaHandler("Sphere.lua");
	luaHandler->RegisterFunctionInScript();
	luaHandler->ExecuteScirpt(model);

}
