#include"SpaceShip.h"
#include <algorithm>


SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;
	model = new Model("Models/Spaceship/Spaceship.obj");
	this->startPos = model->transform.position;

	
}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	
	model->id = "SpaceShip";
	model->transform.SetPosition(glm::vec3(0, 0, 2));
	render->AddModelsAndShader(model, defaultshader);


	SpaceShipPhysics = new PhysicsObject(model);

	SpaceShipPhysics->Initialize(SPHERE, true, DYNAMIC);
	SpaceShipPhysics->gravityValue =0;

	SpaceShipPhysics->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	engine->AddPhysicsObjects(SpaceShipPhysics);

	this->m_startPos = model->transform.position;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;


	
	//this->startRot = model->transform.rotation;
}

void SpaceShip::Update(float deltaTime)
{

	SpaceShipPhysics->velocity = Direction * speed;
	 //CalculateNextWaypoint(deltaTime);
	 CalculateBezierCurve(deltaTime);
	//camera->Position = model->transform.position -  cameraOffset;
}


void SpaceShip::SpaceShipInputs(GLFWwindow* window, float deltaTime)
{
	/*


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

	*/
}

void SpaceShip::MoveSpaceShip(const glm::vec3& targetPosition, const glm::vec3& targetRotation, float deltaTime)
{

	model->transform.position = LerpObject(model->transform.position, targetPosition, movementSpeed * deltaTime);
}

void SpaceShip::CalculateBezierCurve(float deltaTime)
{
	if (waypointIndex < waypoints.size() - 3)
	{
		const Waypoint& p0 = waypoints[waypointIndex];
		const Waypoint& p1 = waypoints[waypointIndex + 1];
		const Waypoint& p2 = waypoints[waypointIndex + 2];
		const Waypoint& p3 = waypoints[waypointIndex + 3];

		float t = elapsedTime / time;
		glm::vec3 curvePosition = CalculateCubicBezier(t, p0.position, p1.position, p2.position, p3.position);

		
		timeStep += deltaTime / time;

		if (time == 0)
		{
			lerpValue = 1;
			timeStep = 1;
		}
		else if (easeInTime != 0 && timeStep <= easeInRatio)
		{
			lerpValue = EaseIn(timeStep / easeInRatio);
			lerpValue *= easeInRatio;
		}
		else if (easeOutTime != 0 && timeStep >= easeOutStart)
		{
			lerpValue = EaseOut((timeStep - easeOutStart) / easeOutRatio);
			lerpValue *= easeOutRatio;
			lerpValue += easeOutStart;
		}
		else
		{
			lerpValue = timeStep;
		}



		model->transform.SetPosition(LerpObject(m_startPos, curvePosition, lerpValue));

	
		glm::vec3 currentPosition = model->transform.position;
		if (glm::distance(currentPosition, p3.position) < 1.5f) {
			
			waypointIndex += 3; 
			
			if (waypointIndex >= waypoints.size() - 3)
			{
				
				waypointIndex = 0;
			}
			elapsedTime = 0.0f; 
			
		}
		else 
		{
			elapsedTime += deltaTime;
		}
	}

}




void SpaceShip::CalculateNextWaypoint(float deltaTime)
{

	timeStep += deltaTime / time;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	
	else
	{
		lerpValue = timeStep;
	}



	model->transform.SetPosition(LerpObject(m_startPos, glm::vec3(95, 95, 0), lerpValue));

	if (waypointIndex < waypoints.size())
	{
		const Waypoint& CurWaypoint = waypoints[waypointIndex];
		
		


		//MoveSpaceShip(CurWaypoint.position, model->transform.rotation, deltaTime);
		 
		glm::vec3 currentPosition = model->transform.position;
		if (glm::distance(currentPosition, CurWaypoint.position) < 1.5f) 
		{

			waypointIndex ++;

			if (waypointIndex == waypoints.size())
			{
				waypointIndex = 0;
			}
		}
		
	}

}

glm::vec3 SpaceShip::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}

glm::vec3 SpaceShip::LerpWithTime(float currentTime, const glm::vec3& startValue, const glm::vec3& endValue, float totalDuration)
{
	
		// Ensure currentTime is within the valid range [0, totalDuration]
		currentTime = std::clamp(currentTime, 0.0f, totalDuration);

		// Normalize currentTime to the range [0, 1]
		float t = currentTime / totalDuration;

		// Perform linear interpolation
		glm::vec3 lerpedValue = startValue + (endValue - startValue) * t;

		return lerpedValue;
	
}

float SpaceShip::EaseIn(float time)
{
	if (time < 0.0f)
	{
		time = 0;
	}
	else if (time > 1.0f)
	{
		time = 1.0f;
	}

	return 1 - std::cos((time * 3.14) / 2);
		
}

float SpaceShip::EaseOut(float time)
{
	if (time < 0.0f)
	{
		time = 0;
	}
	else if (time > 1.0f)
	{
		time = 1.0f;
	}

	
    return std::sin((time * 3.14) / 2);
}



glm::vec3 SpaceShip::CalculateCubicBezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 result;
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	result = uuu * p0 + 5 * uu * t * p1 + 3 * u * tt * p2 + ttt * p3;

	return result;
}
