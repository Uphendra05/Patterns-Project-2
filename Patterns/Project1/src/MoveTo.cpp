#include "MoveTo.h"


MoveTo::MoveTo() : model(nullptr)
{
	
	this->StartPosition = glm::vec3(0);
	this->endPosition = glm::vec3(0);
}

MoveTo::MoveTo( Model*& model , const glm::vec3& endPosition)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;

}

MoveTo::MoveTo(Model*& model, const glm::vec3& endPosition, const float& time)
{
    this->model = model;
    this->StartPosition = glm::vec3(0);
    this->endPosition = endPosition;
    this->time = time;
}

MoveTo::MoveTo(Model*& model, const glm::vec3& endPosition, const float& time, const float& easeIn)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;
}

MoveTo::MoveTo(Model*& model, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut)
{
	this->model = model;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;
	this->easeOutStart = easeOut;
}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;

	this->model = nullptr;

}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;
	this->easeOutTime = easeOut;
	this->model = nullptr;
}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn, EaseType& easInType)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;
	this->EaseIn_State = easInType;

	this->model = nullptr;
}

MoveTo::MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut, EaseType& easInType, EaseType& easOutType)
{
	this->gameObject = gameObject;
	this->StartPosition = glm::vec3(0);
	this->endPosition = endPosition;
	this->time = time;
	this->easeInTime = easeIn;
	this->easeOutTime = easeOut;

	this->EaseIn_State = easInType;
	this->EaseOut_State = easOutType;

	this->model = nullptr;
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
	std::cout << "MOVE to start" << std::endl;
	//if (!model->isVisible)
	//{
	//	model->isVisible = true;
	//}
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
		lerpValue = EaseIn( EaseIn_State, timeStep / easeInRatio);
		lerpValue *= easeInRatio;
	}
	else if (easeOutTime != 0 && timeStep >= easeOutStart)
	{
		lerpValue = EaseOut(EaseOut_State,(timeStep - easeOutStart) / easeOutRatio);
		lerpValue *= easeOutRatio;
		lerpValue += easeOutStart;
	}
	else
	{
		lerpValue = timeStep;
	}
	//model->transform.SetPosition(LerpObject(StartPosition, endPosition, lerpValue));

	gameObject->GetTransform()->SetPosition(LerpObject(StartPosition, endPosition, lerpValue));
}

void MoveTo::SetStarted(bool isStarted)
{
    isStart = isStarted;
}

bool MoveTo::IsComplete()
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

bool MoveTo::IsStarted()
{
    return isStart;
}

glm::vec3 MoveTo::GetModelPosition()
{
	return gameObject->GetTransform()->position;
}

glm::vec3 MoveTo::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}



