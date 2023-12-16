#pragma once
//#include "model.h"
#include "Command.h"
#include "GameObject.h"

class FollowObject : public Command
{
public:
	FollowObject();
	FollowObject(float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset);
	FollowObject(Model* currentModel, Model* followModel,float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset);
	FollowObject(GameObject* currentGameObject, GameObject* followObject, float time ,float maxFollowSpeed, float accelerationRange, float decelerationRange, float followDistance, glm::vec3 followOffset);
	~FollowObject();

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	 bool IsComplete() override;
	 bool IsStarted() override;

private:
	Model* model;
	Model* FollowModel;

	float maxFollowSpeed;
	float accelerationRange;
	float decelerationRange;
	float followDistance;
	float time;
	float timeStep;

	glm::vec3 followOffset;

	glm::vec3 currentPosition;
	glm::vec3 targetPosition;

	GameObject* gameobject;
	GameObject* FollowGameObject;
	float CalculateFollowSpeed(float distanceToTarget);
};

