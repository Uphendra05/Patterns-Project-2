#include "OrientTo.h"

OrientTo::OrientTo(Model* model, glm::vec3& targetPos, float time)
{
	this->model = model;
	this->targetPos = targetPos;
	this->time = time;
}

OrientTo::OrientTo()
{
}

OrientTo::~OrientTo()
{
}

void OrientTo::Start()
{

	this->m_startPos = model->transform.position;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;
}

void OrientTo::Update(float deltaTime)
{

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
	model->transform.SetRotation(LerpObject(m_startPos, targetPos, lerpValue));

}

void OrientTo::End()
{
}

float OrientTo::EaseIn(float time)
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

float OrientTo::EaseOut(float time)
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

glm::vec3 OrientTo::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}
