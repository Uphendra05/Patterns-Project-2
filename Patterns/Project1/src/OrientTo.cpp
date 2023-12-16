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

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation)
{

	this->gameObject = gameobject;
	this->endRotation = endRotation;
}

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation, const float& time)
{
	this->gameObject = gameobject;
	this->endRotation = endRotation;
	this->time = time;


}

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation, const float& time, const float& easeIn)
{
	this->gameObject = gameobject;
	this->endRotation = endRotation;
	this->time = time;

	this->easeInTime =easeIn;

	
}

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation, const float& time, const float& easeIn, const float& easeOut)
{
	this->gameObject = gameobject;
	this->endRotation = endRotation;
	this->time = time;

	this->easeInTime - easeIn;
	this->easeOutTime = easeOut;
}

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation, const float& time, const float& easeIn, const float& easeOut, EaseType& easeInType)
{
	this->gameObject = gameobject;
	this->endRotation = endRotation;
	this->time = time;

	this->easeInTime - easeIn;
	this->easeOutTime = easeOut;

	//Ease type
	this->EaseIn_State = easeInType;
}

OrientTo::OrientTo(GameObject*& gameobject, const glm::vec3& endRotation, const float& time, const float& easeIn, const float& easeOut, EaseType& easeInType, EaseType& easeOutType)
{
	this->gameObject = gameobject;
	this->endRotation = endRotation;
	this->time = time;

	this->easeInTime - easeIn;
	this->easeOutTime = easeOut;

	//Ease type
	this->EaseIn_State = easeInType;
	this->EaseOut_State = easeOutType;

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
		lerpValue = EaseIn(EaseIn_State,timeStep / easeInRatio);
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


	gameObject->GetTransform()->SetRotation(LerpObject(StartRotation, endRotation, lerpValue));


//	gameObject->model->transform.SetRotation(LerpObject(StartRotation, endRotation, lerpValue));
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
	//return model->transform.rotation;
	return gameObject->GetTransform()->rotation;
}

glm::vec3 OrientTo::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}

