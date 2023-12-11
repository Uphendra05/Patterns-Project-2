
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
    glm::vec3 direction = (FollowModel->transform.position - model->transform.position);
    model->transform.SetPosition(followOffset + direction * followDistance);
}

void FollowObject::Update(float deltatime)
{
    if (!isStart) {
        return; 
    }

    glm::vec3 direction = glm::normalize(FollowModel->transform.position - model->transform.position);
    float distanceToTarget = glm::length(FollowModel->transform.position - model->transform.position);
    float followSpeed = CalculateFollowSpeed(distanceToTarget);

    glm::vec3 newPosition = model->transform.position + direction * followSpeed * deltatime;

    glm::vec3 followPosition = FollowModel->transform.position - direction * followDistance + followOffset;

  //float smoothingFactor = glm::clamp(deltatime * 1, 0.0f, 1.0f);

    newPosition = glm::mix(newPosition, followPosition, deltatime * 1);

    model->transform.SetPosition(newPosition);
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
    const float rangeDifference = decelerationRange - accelerationRange;

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
        float t = 1.0f - (distanceToTarget - accelerationRange) / rangeDifference;
        return maxFollowSpeed * t;
    }
}
