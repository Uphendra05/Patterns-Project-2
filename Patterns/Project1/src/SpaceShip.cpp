#include"SpaceShip.h"
#include "Singleton.h"

SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;

	//this->m_LuaHandler = new LuaHandler("SpaceShip.lua");
	//m_LuaHandler->RegisterFunctionInScript();
	
}

SpaceShip::SpaceShip()
{
	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	LoadModel();

	SetActive(false);
}

SpaceShip::SpaceShip(const std::string id)
{
	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->id = id;

	LoadModel();

	SetActive(false);

}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	model = new Model("Models/SpaceShip/SpaceShip.ply");
	if (id.empty())
	{
		id = "SPACESHIP";
	}

	model->id = id;
	model->transform.SetPosition(glm::vec3(0, 0,0));
	model->transform.SetScale(glm::vec3(0.05f));
	render->AddModelsAndShader(model, defaultshader);


	//m_LuaHandler->ExecuteScirpt(model);  // Executing Lua 
}

void SpaceShip::Update(float deltaTime)
{


	
}

void SpaceShip::SetActive(const bool& isactive)
{
	model->isVisible = isactive;
}


