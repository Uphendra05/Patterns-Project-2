#include "LookAt.h"



LookAt::LookAt(GameObject* gameObject, GameObject* lookAtObject, float time)
{
	this->gameObject = gameObject;
	this->lookAtObject = lookAtObject;
	this->time = time;
}

LookAt::~LookAt()
{
}

void LookAt::Start()
{
	
}

void LookAt::Update(float deltatime)
{
	timeStep += deltatime;

	distance = lookAtObject->GetTransform()->position - gameObject->GetTransform()->position;

//if (distance == glm::vec3(0)) return;

	direction = glm::normalize(distance);

	right = glm::cross(glm::vec3(0, 1, 0), direction);
	up = glm::cross(direction, right);

	gameObject->GetTransform()->SetOrientationFromDirections(up, right);

	if (gameObject->id =="CAMERA")
	{
         float pitch = gameObject->GetTransform()->rotation.x;
		
         pitch = glm::clamp(pitch, -89.0f, 89.0f);

	  //gameObject->GetTransform()->SetRotation(glm::vec3(pitch,gameObject->GetTransform()->rotation.y, 0));
		return;
	}

	gameObject->GetTransform()->SetRotation(gameObject->GetTransform()->rotation + lookAtOffset);

}

void LookAt::SetStarted(bool isStarted)
{
}

bool LookAt::IsComplete()
{
	if (timeStep >= time)
	{
		return true;
	}
	return false;
}

bool LookAt::IsStarted()
{
	return false;
}
