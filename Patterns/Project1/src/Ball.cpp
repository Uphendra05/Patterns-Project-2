
#include "Ball.h"

Ball::Ball(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;

	m_LuaHandler = new LuaHandler("Sphere.lua");
	m_LuaHandler->RegisterFunctionInScript();
}

Ball::~Ball()
{
}

void Ball::LoadModel()
{
	model = new Model("Models/DefaultSphere/Sphere.ply");
	model->id = "Ball";
	model->transform.SetPosition(glm::vec3(0, 0, 0));
	render->AddModelsAndShader(model, defaultshader);


	ballPhysics = new PhysicsObject(model);

	ballPhysics->Initialize(SPHERE, true, DYNAMIC);
	ballPhysics->gravityValue = 0;

	ballPhysics->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	engine->AddPhysicsObjects(ballPhysics);


	m_LuaHandler->ExecuteScirpt(model);  // Executing Lua 
}
