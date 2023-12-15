#include "MoveAlongOneAxisWithTime.h"


MoveAlongAxisWithTime::MoveAlongAxisWithTime(Model* model, int Axis, float time,float speed )
{
	this->model = model;
	this->axis = Axis;
	this->time = time;
	this->speed = speed;
}

MoveAlongAxisWithTime::~MoveAlongAxisWithTime()
{
}

void MoveAlongAxisWithTime::Start()
{
	timeStep = 0;

	if (!model->isVisible)
	{
		model->isVisible = true;
	}
}

void MoveAlongAxisWithTime::Update(float deltatime)
{
	timeStep += deltatime;

	switch (axis)
	{
	case 1:
		model->transform.position.x += deltatime * speed;
		break;

	case 2:
		model->transform.position.y += deltatime * speed;
		break;

	case 3:
		model->transform.position.z += deltatime * speed;
		break;
	default:
		break;
	}
}

void MoveAlongAxisWithTime::SetStarted(bool isStarted)
{
}

bool MoveAlongAxisWithTime::IsComplete()
{
	if (timeStep >= time)
	{
		return true;
	}
	return false;
}

bool MoveAlongAxisWithTime::IsStarted()
{
	return false;
}
