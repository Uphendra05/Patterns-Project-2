#include "WaitForSeconds.h"

WaitForSecond::WaitForSecond(float time)
{
	this->time = time;
}

WaitForSecond::~WaitForSecond()
{
}

void WaitForSecond::Start()
{
	timeStep = 0;
}

void WaitForSecond::Update(float deltatime)
{
	timeStep += deltatime;
}

void WaitForSecond::SetStarted(bool isStarted)
{
}

bool WaitForSecond::IsComplete()
{
	if (timeStep >= time)
	{
		return true;
	}
	return false;
}

bool WaitForSecond::IsStarted()
{
	return false;
}
