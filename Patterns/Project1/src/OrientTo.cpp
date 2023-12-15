#include "OrientTo.h"


OrientTo::OrientTo() : model(nullptr)
{

	this->StartRotation = glm::vec3(0);
	this->endRotation = glm::vec3(0);
}

OrientTo::OrientTo(Model*& model, const glm::vec3& endRotation)
{
	this->model = model;
	this->StartRotation = glm::vec3(0);
	this->endRotation = endRotation;

}

OrientTo::OrientTo(Model*& model, const glm::vec3& endRotation, const float& time)
{
	this->model = model;
	this->StartRotation = glm::vec3(0);
	this->endRotation = endRotation;
	this->time = time;
}

OrientTo::OrientTo(Model*& model, const glm::vec3& endRotation, const float& time, const float& easeIn)
{
	this->model = model;
	this->StartRotation = glm::vec3(0);
	this->endRotation = endRotation;
	this->time = time;
	this->easeInTime = easeIn;
}

OrientTo::OrientTo(Model*& model, const glm::vec3& endRotation, const float& time, const float& easeIn, const float& easeOut)
{
	this->model = model;
	this->StartRotation = glm::vec3(0);
	this->endRotation = endRotation;
	this->time = time;
	this->easeInTime = easeIn;
	this->easeOutStart = easeOut;
}

OrientTo::~OrientTo()
{

}

void OrientTo::SetModel(Model& model)
{
	this->model = &model;
}

void OrientTo::Start()
{
	StartRotation = GetModelRotaion();

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;

	isAnimationCompleted = false;

	if (!model->isVisible)
	{
		model->isVisible = true;
	}
}

void OrientTo::Update(float deltaTime)
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
	model->transform.SetRotation(LerpObject(StartRotation, endRotation, lerpValue));
}

void OrientTo::SetStarted(bool isStarted)
{
	isStart = isStarted;
}

bool OrientTo::IsComplete()
{
	if (!updatedOnce)
	{
		return false;
	}
	if (lerpValue >= 1)
	{
		return true;
	}

	return false;
}

bool OrientTo::IsStarted()
{
	return isStart;
}

glm::vec3 OrientTo::GetModelRotaion()
{
	return model->transform.rotation;
}

glm::vec3 OrientTo::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
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