
#include "Ball.h"
#include "Singleton.h"

Ball::Ball()
{


	this->render = Singleton::GetInstance().GetRenderer();
	this->defaultshader = Singleton::GetInstance().GetDefaultShader();
	this->engine = Singleton::GetInstance().GetPhysicsEngine();

	Singleton::GetInstance().AddGameObject(this);

	LoadModel();
}

Ball::~Ball()
{
}

void Ball::LoadModel()
{
	Model* cube = Singleton::GetInstance().GetDefaultCube();

	//model = new Model("Models/DefaultSphere/Sphere.ply");
	model = new Model(*cube);
	model->id = "BALL";
	SetGameObjectId(model->id);
	model->transform.SetPosition(glm::vec3(1));
	render->AddModelsAndShader(model, defaultshader);


	/*ballPhysics = new PhysicsObject(model);

	ballPhysics->Initialize(SPHERE, true, DYNAMIC);
	ballPhysics->gravityValue = 0;

	ballPhysics->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	engine->AddPhysicsObjects(ballPhysics);*/


	//m_LuaHandler->ExecuteScirpt(model);  // Executing Lua 
}

Transform* Ball::GetTransform()
{
	return &model->transform;
}
