#include "SpawnObject.h"


void SpawnObject::Start()
{
	timeStep = 0;
}

void SpawnObject::Update(float deltatime)
{
	timeStep += deltatime;

	

}

void SpawnObject::SetStarted(bool isStarted)
{
}

bool SpawnObject::IsComplete()
{
	if (timeStep>=time)
	{
		if (!gameObject->model->isVisible)
		{
			gameObject->model->isVisible = true;
		}

		return true;
	}
	return false;
}

bool SpawnObject::IsStarted()
{
	return isStart;
}

SpawnObject::SpawnObject(GameObject* gameObject, float time)
{
	this->gameObject = gameObject;
	this->time = time;

}

SpawnObject::~SpawnObject()
{
}

SpawnObject::SpawnObject(Model* model)
{

}

