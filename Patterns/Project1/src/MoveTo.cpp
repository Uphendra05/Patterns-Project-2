#include "MoveTo.h"


MoveTo::MoveTo() : model(nullptr)
{
	
	this->StartPosition = glm::vec3(0);
	this->endPosition = glm::vec3(0);
}

MoveTo::MoveTo( Model*& model , const glm::vec3& targetPosition)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = targetPosition;

}

MoveTo::MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time)
{
    this->model = model;
    this->StartPosition = glm::vec3(0);
    this->endPosition = targetPosition;
    this->time = time;
}

MoveTo::MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time, const float& easeIn)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = targetPosition;
	this->time = time;
	this->easeInTime = easeIn;
}

MoveTo::MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time, const float& easeIn, const float& easeOut)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = targetPosition;
	this->time = time;
	this->easeInTime = easeIn;
	this->easeOutStart = easeOut;
}

MoveTo::~MoveTo()
{

}

void MoveTo::SetModel(Model& model)
{
	this->model = &model;
}

void MoveTo::Start()
{
	StartPosition = GetModelPosition();

    easeInRatio = easeInTime / time;
    easeOutRatio = easeOutTime / time;

    easeOutStart = 1 - easeOutRatio;

    timeStep = 0;

	isAnimationCompleted = false;
}

void MoveTo::Update(float deltaTime)
{
    if (isAnimationCompleted)
    {
        return;
    }
       
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
	model->transform.SetPosition(LerpObject(StartPosition, endPosition, lerpValue));
}

void MoveTo::SetStarted(bool isStarted)
{
    isStart = isStarted;
}

bool MoveTo::IsComplete()
{

	return lerpValue >= 1;
}

bool MoveTo::IsStarted()
{
    return isStart;
}

glm::vec3 MoveTo::GetModelPosition()
{
	return model->transform.position;
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