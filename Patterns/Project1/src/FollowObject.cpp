
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

FollowObject::FollowObject(GameObject* currentGameObject, GameObject* followObject, float time, float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset)
{
    this->gameobject = currentGameObject;
    this->FollowGameObject = followObject;

    this->maxFollowSpeed = maxFollowSpeed;
    this->accelerationRange = accelerationRange;
    this->decelerationRange = decelerationRange;
    this->followDistance = followDistance;
    this->followOffset = followOffset;
    this->time = time;
}

FollowObject::~FollowObject()
{
}

void FollowObject::Start()
{
    glm::vec3 direction = (FollowGameObject->GetTransform()->position - gameobject->GetTransform()->position);

    gameobject->GetTransform()->SetPosition(followOffset + direction * followDistance);
    timeStep = 0;
}

void FollowObject::Update(float deltatime)
{
    timeStep += deltatime;

    glm::vec3 direction = glm::normalize(FollowGameObject->GetTransform()->position - gameobject->GetTransform()->position);
    float distanceToTarget = glm::length(FollowGameObject->GetTransform()->position - gameobject->GetTransform()->position);
    float followSpeed = CalculateFollowSpeed(distanceToTarget);

    glm::vec3 newPosition = gameobject->GetTransform()->position + direction * followSpeed * deltatime;

    glm::vec3 followPosition = FollowGameObject->GetTransform()->position - direction * followDistance + followOffset;

  //float smoothingFactor = glm::clamp(deltatime * 1, 0.0f, 1.0f);

    newPosition = glm::mix(newPosition, followPosition, deltatime * 1);

    gameobject->GetTransform()->SetPosition(newPosition);
}

void FollowObject::SetStarted(bool isStarted)
{
    isStart = isStarted;
}

bool FollowObject::IsComplete()
{
    if (timeStep>= time)
    {
        return true;
    }
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
