#pragma once

#include "Command.h"
#include "GameObject.h"
#include"EasingTechiques.h"
#include "CubicBezierCurve.h"
class FollowCurveWithTime : public Command
{
public:
	FollowCurveWithTime(GameObject* gameObject, float time);
	~FollowCurveWithTime();

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

	void SetBezierCurve(CubicBezierCurve* curve);
	void AddPoint(const glm::vec3& point, const glm::vec3& controlPoint, const glm::vec3& rotationOffset);
	void SetLookAtTangent(bool state);
	void SetLookAtOffset(const glm::vec3& offset);

private:

	GameObject* gameObject;

	int currentPointIndex = 0;

	bool lookAtTangent = 0;

	float time;
	float lerpTime = 0;
	float lerpValue = 0;
	float timeStep = 0;
	float deltaTime = 0;

	float timeStepCurve = 0;


	glm::vec3 right;
	glm::vec3 dir;
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 lookAtOffset = glm::vec3(0);

	PointOnCurve startPos{ glm::vec3(0), glm::vec3(0),  glm::vec3(0) };
	PointOnCurve targetPos{ glm::vec3(0), glm::vec3(0),glm::vec3(0) };

	CubicBezierCurve* curve = nullptr;

	float easeInTime = 0;
	float easeOutTime = 0;

	float easeInRatio = 0;
	float easeOutRatio = 0;

	float easeInStart = 0;
	float easeOutStart = 0;

	EaseType easeInMode = NONE;
	EaseType easeOutMode= NONE;
};

