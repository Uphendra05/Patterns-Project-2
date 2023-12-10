#include "FollowObject.h"



FollowObject::FollowObject(float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset)
{

	this->maxFollowSpeed = maxFollowSpeed;
	this->accelerationRange = accelerationRange;
	this->decelerationRange = decelerationRange;
	this->followDistance = followDistance;
	this->followOffset = followOffset;
}

FollowObject::~FollowObject()
{
}

void FollowObject::Update( glm::vec3& currentPosition, const glm::vec3& targetPosition, float deltaTime)
{
    float distanceToTarget = glm::distance(currentPosition, targetPosition);

    // Determine the follow speed based on the distance
    float followSpeed = CalculateFollowSpeed(distanceToTarget);

    // Move towards the target with the calculated speed
    glm::vec3 direction = glm::normalize(targetPosition - currentPosition);
    glm::vec3 newPosition = currentPosition + direction * followSpeed * deltaTime;

    // Apply follow distance and offset
    glm::vec3 followPosition = targetPosition - glm::normalize(direction) * followDistance + followOffset;
    newPosition = glm::mix(newPosition, followPosition, deltaTime * 3.0f);  // Adjust 2.0f as needed for smoother interpolation

    currentPosition = newPosition;


}
