#pragma once
#include "model.h"
#include "Command.h"
class OrientTo : public Command
{
public:
	
	OrientTo();
	~OrientTo();
	
	OrientTo(Model*& model, const glm::vec3& endRotation);
	OrientTo(Model*& model, const glm::vec3& endRotation, const float& time);
	OrientTo(Model*& model, const glm::vec3& endRotation, const float& time, const float& easeIn);
	OrientTo(Model*& model, const glm::vec3& endRotation, const float& time, const float& easeIn, const float& easeOut);

	void SetModel(Model& model);

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;


	glm::vec3 GetModelRotaion();
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

	glm::vec3 endRotation;
	glm::vec3 StartRotation;
};

