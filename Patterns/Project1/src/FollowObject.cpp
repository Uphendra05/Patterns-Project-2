
#include "FollowObject.h"

FollowObject::FollowObject()
{
}

FollowObject::FollowObject(float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset)
{
    this->maxFollowSpeed = maxFollowSpeed;
    this->accelerationRange = accelerationRange;
    this->decelerationRange = decelerationRange;
    this->followDistance = followDistance;
    this->followOffset = followOffset;
}

FollowObject::FollowObject(Model* currentModel, Model* followModel, float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset)
{

    this->maxFollowSpeed = maxFollowSpeed;
    this->accelerationRange = accelerationRange;
    this->decelerationRange = decelerationRange;
    this->followDistance = followDistance;
    this->followOffset = followOffset;

    this->model = currentModel;
    this->FollowModel = followModel;
}

FollowObject::~FollowObject()
{
}

void FollowObject::Start()
{
    currentPosition = model->transform.position;
    targetPosition = FollowModel->transform.position;
}

void FollowObject::Update(float deltatime)
{
    if (!isStart) {
        return;  // Stop updating if not started
    }

    float distanceToTarget = glm::distance(model->transform.position, FollowModel->transform.position);
    float followSpeed = CalculateFollowSpeed(distanceToTarget);

    glm::vec3 direction = glm::normalize(FollowModel->transform.position - model->transform.position);
    glm::vec3 newPosition = model->transform.position + direction * followSpeed * deltatime;

    glm::vec3 followPosition = FollowModel->transform.position - glm::normalize(direction) * followDistance + followOffset;
    newPosition = glm::mix(newPosition, followPosition, deltatime * 0.2f);

    model->transform.position = newPosition;
}

void FollowObject::SetStarted(bool isStarted)
{
    isStart = isStarted;
}

bool FollowObject::IsComplete()
{
	return false;
}

bool FollowObject::IsStarted()
{
	return isStart;
}

float FollowObject::CalculateFollowSpeed(float distanceToTarget)
{
    if (distanceToTarget > decelerationRange) 
    {
        return maxFollowSpeed;
    }
    else if (distanceToTarget < accelerationRange) 
    {
        
        return 0.0f;
    }
    else 
    {
        float t = 1.0f - (distanceToTarget - accelerationRange) / (decelerationRange - accelerationRange);
        return maxFollowSpeed * t;
    }
}
