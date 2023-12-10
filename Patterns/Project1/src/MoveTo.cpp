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

void MoveTo::Update(float deltaTime)
{
    if (isAnimationCompleted)
    {
        return;
    }
        glm::vec3 direction = glm::normalize(endPosition - StartPosition);
        float distance = glm::distance(GetModelPosition(), endPosition);


        const float epsilon = 0.1f;
        if (distance < epsilon)
        {
            isAnimationCompleted = true;
        }
        else
        {
            // Move the object along the direction
            model->transform.position += direction * deltaTime;
        }
    
}

void MoveTo::SetStarted(bool isStarted)
{
    isStart = isStarted;
}

bool MoveTo::IsComplete()
{

    
       return isAnimationCompleted;
    

}

bool MoveTo::IsStarted()
{
    return isStart;
}

glm::vec3 MoveTo::GetModelPosition()
{
	return model->transform.position;
}
