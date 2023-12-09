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
	isAnimationCompleted = false;
}

void MoveTo::Update(float deltatime)
{
	glm::vec3 direction = glm::normalize(StartPosition - endPosition);
	if (glm::distance(StartPosition, endPosition) > 0.1f)
	{
		model->transform.position += direction * deltatime;
	}
	else
	{
		isAnimationCompleted = true;
	}
}

bool MoveTo::IsComplete()
{
	return isAnimationCompleted;
}

glm::vec3 MoveTo::GetModelPosition()
{
	return model->transform.position;
}
