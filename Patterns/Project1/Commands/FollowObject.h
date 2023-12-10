#pragma once

#include <iostream>
#include "../../src/model.h"

class FollowObject
{
public:
	FollowObject(float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset);
	~FollowObject();

    void Update( glm::vec3& currentPosition, const glm::vec3& targetPosition, float deltaTime);


private:

    float maxFollowSpeed;
    float accelerationRange;
    float decelerationRange;
    float followDistance;
    glm::vec3 followOffset;

    float CalculateFollowSpeed(float distanceToTarget) {
        if (distanceToTarget > decelerationRange) {
            // Beyond the deceleration range, move at the max speed
            return maxFollowSpeed;
        }
        else if (distanceToTarget < accelerationRange) {
            // Within the acceleration range, don't move
            return 0.0f;
        }
        else {
            // Between acceleration and deceleration ranges, interpolate speed
            float t = 1.0f - (distanceToTarget - accelerationRange) / (decelerationRange - accelerationRange);
            return maxFollowSpeed * t;
        }
    }
};

