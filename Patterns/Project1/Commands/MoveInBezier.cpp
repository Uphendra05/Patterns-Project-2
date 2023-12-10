#include "MoveInBezier.h"

MoveInBezier::MoveInBezier(Model* model, glm::vec3& targetPos, float time)
{

	this->model = model;
	this->targetPos = targetPos;
	this->time = time;


}

MoveInBezier::~MoveInBezier()
{
}

void MoveInBezier::Start()
{

	this->m_startPos = model->transform.position;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;
}

void MoveInBezier::Update(float deltaTime)
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
	model->transform.SetPosition(LerpObject(m_startPos, targetPos, lerpValue));
}

void MoveInBezier::End()
{
}

float MoveInBezier::EaseIn(float time)
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

float MoveInBezier::EaseOut(float time)
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

glm::vec3 MoveInBezier::CalculateCubicBezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
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

glm::vec3 MoveInBezier::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}
