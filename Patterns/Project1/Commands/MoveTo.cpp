#include "MoveTo.h"

MoveTo::MoveTo(Model* model, glm::vec3& targetPos, float time)
{
	this->model = model;
	this->targetPos = targetPos;
	this->time = time;

}

MoveTo::MoveTo()
{


}

MoveTo::~MoveTo()
{



}

void MoveTo::Start()
{
	this->m_startPos = model->transform.position;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;


}

void MoveTo::Update(float deltaTime)
{

	timeStep += deltaTime / time;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else if (easeInTime != 0 && timeStep <= easeInRatio)
	{
		lerpValue = EaseIn( timeStep / easeInRatio);
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

void MoveTo::End()
{
}

glm::vec3 MoveTo::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}


float MoveTo::EaseIn(float time)
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

float MoveTo::EaseOut(float time)
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