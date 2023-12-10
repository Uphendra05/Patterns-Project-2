#include"SpaceShip.h"

SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;

	this->m_LuaHandler = new LuaHandler("SpaceShip.lua");
	m_LuaHandler->RegisterFunctionInScript();

}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	model = new Model("Models/Spaceship/Ship2.obj");
	model->id = "SpaceShip";
	model->transform.SetPosition(glm::vec3(0, 0,0));
	render->AddModelsAndShader(model, defaultshader);


	SpaceShipPhysics = new PhysicsObject(model);

	SpaceShipPhysics->Initialize(SPHERE, true, DYNAMIC);
	SpaceShipPhysics->gravityValue =0;

	SpaceShipPhysics->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	engine->AddPhysicsObjects(SpaceShipPhysics);


	m_LuaHandler->ExecuteScirpt(model);  // Executing Lua 
}

void SpaceShip::Update(float deltaTime)
{

	SpaceShipPhysics->velocity = Direction * speed;

	camera->transform.position = model->transform.position -  cameraOffset;
}

void SpaceShip::SpaceShipInputs(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		//Direction = glm::vec3(0, 0, 1);
		Direction = -model->transform.GetForward();
		//camera->Position += -model->transform.GetForward() * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		//Direction = glm::vec3(0, 0, -1);
		Direction = model->transform.GetForward();
	}
	else   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Direction = model->transform.GetRight();
	}
	else  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Direction = -model->transform.GetRight();
	}
	else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Direction = model->transform.GetUp();
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Direction = -model->transform.GetUp();
	}
	else
	{
		Direction = glm::vec3(0, 0, 0);
	}

	
}
