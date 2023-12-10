#pragma once
#include <iostream>
#include "../../src/model.h"


class MoveInBezier
{

	MoveInBezier(Model* model, glm::vec3& targetPos, float time);
	~MoveInBezier();


	void Start();
	void Update(float deltaTime);
	void End();

	static float EaseIn(float time);
	static float EaseOut(float time);

	glm::vec3 CalculateCubicBezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);


	glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);

private:

	float easeInTime = 0;
	float easeOutTime = 0;

	float easeInRatio = 0;
	float easeOutRatio = 0;

	float easeInStart = 0;
	float easeOutStart = 0;

	float time;
	float timeStep = 0;
	float lerpValue = 0;


	Model* model;
	glm::vec3 targetPos;


	glm::vec3 m_startPos;

};

