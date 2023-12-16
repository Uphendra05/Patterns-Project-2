#pragma once

#include "Command.h"
#include "GameObject.h"




class LookAt : public Command
{
public:
	LookAt(GameObject* gameObject, GameObject* lookAtObject, float time);
	~LookAt();

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	 bool IsComplete() override;
	 bool IsStarted() override;

private:

	float time = 0;
	float timeStep = 0;


	glm::vec3 distance = glm::vec3(0);
	glm::vec3 direction = glm::vec3(0);
	glm::vec3 right = glm::vec3(0);
	glm::vec3 up = glm::vec3(0);

	glm::vec3 lookAtOffset = glm::vec3(0);

	GameObject* gameObject;
	GameObject* lookAtObject;
};

