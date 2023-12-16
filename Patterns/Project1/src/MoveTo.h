#pragma once


#include "GameObject.h"
#include "EasingTechiques.h"
#include "Command.h"

class MoveTo : public Command
{
public:
	MoveTo();
	MoveTo(Model*& model, const glm::vec3& endPosition);
	MoveTo(Model*& model, const glm::vec3& endPosition, const float& time);
	MoveTo(Model*& model, const glm::vec3& endPosition, const float& time, const float& easeIn);
	MoveTo(Model*& model, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut);


	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition);
	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time);
	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn);
	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut);

	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn,EaseType& easInType);
	MoveTo(GameObject*& gameObject, const glm::vec3& endPosition, const float& time, const float& easeIn, const float& easeOut,EaseType& easInType,  EaseType& easOutType);

	 ~MoveTo();

	void SetModel(Model& model);

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	 bool IsComplete() override;
	 bool IsStarted() override;


	 glm::vec3 GetModelPosition();
	 glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);


	 EaseType EaseIn_State = EaseType::NONE;
	 EaseType EaseOut_State = EaseType::NONE;


private:
	
	Model* model = nullptr;

	GameObject* gameObject;

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

