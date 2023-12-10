#pragma once

#include "model.h"
#include "Command.h"

class MoveTo : public Command
{
public:
	MoveTo();
	MoveTo(Model*& model, const glm::vec3& targetPosition);
	MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time);
	MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time, const float& easeIn);
	MoveTo(Model*& model, const glm::vec3& targetPosition, const float& time, const float& easeIn, const float& easeOut);
	 ~MoveTo();

	void SetModel(Model& model);

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	 bool IsComplete() override;
	 bool IsStarted() override;


	 glm::vec3 GetModelPosition();
	 glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);



	 static float EaseIn(float time);
	 static float EaseOut(float time);

private:
	
	Model* model;

	bool isAnimationCompleted = false;

	float easeInTime = 0;
	float easeOutTime = 0;

	float easeInRatio = 0;
	float easeOutRatio = 0;

	float easeInStart = 0;
	float easeOutStart = 0;

	float time = 1;
	float timeStep = 0;
	float lerpValue = 0;

	glm::vec3 endPosition;
	glm::vec3 StartPosition;
};

