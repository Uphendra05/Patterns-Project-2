#include "RotateAlongAxisWithTime.h"


RotateAlongAxisWithTime::RotateAlongAxisWithTime(Model* model, int Axis, float time, float speed)
{
	this->model = model;
	this->rotationAxis = Axis;
	this->time = time;
	this->speed = speed;
}

RotateAlongAxisWithTime::~RotateAlongAxisWithTime()
{
}

void RotateAlongAxisWithTime::Start()
{
	timeStep = 0;
}

void RotateAlongAxisWithTime::Update(float deltatime)
{
	timeStep += deltatime;

	switch (rotationAxis)
	{
	case 1: //X
		model->transform.rotation.x += deltatime * speed;
		break;

	case 2: // Y
		model->transform.rotation.y += deltatime * speed;
		break;

	case 3: // Z
		model->transform.rotation.z += deltatime * speed;
		break;
	default:
		break;
	}
}

void RotateAlongAxisWithTime::SetStarted(bool isStarted)
{
	isStart = isStarted;
}

bool RotateAlongAxisWithTime::IsComplete()
{
	if (timeStep >= time)
	{
		return true;
	}
	return false;
}

bool RotateAlongAxisWithTime::IsStarted()
{
	return isStart;
}
