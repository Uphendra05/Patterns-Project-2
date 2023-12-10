#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"

#include "../../Commands/MoveTo.h"

struct Waypoint {
	glm::vec3 position;
	glm::vec3 rotation;
};

class SpaceShip
{
public:
	SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera);
	SpaceShip();
	~SpaceShip();


	Model* model;
	PhysicsObject* SpaceShipPhysics;
	

	std::vector<Waypoint> waypoints = {
	{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f)},  // Waypoint 0
	{glm::vec3(10.0f, -10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},    // Waypoint 1
	{glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f)},   // Waypoint 2
	{glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)}    // Waypoint 3
	};

	float movementSpeed = .5f;
	int waypointIndex;
	float elapsedTime;
	void LoadModel();

	void Update(float deltaTime);
	
	void SpaceShipInputs(GLFWwindow* window, float deltaTime);

	void MoveSpaceShip(const glm::vec3& targetPosition, const glm::vec3& targetRotation, float deltaTime);
	void CalculateBezierCurve(float deltaTime);
	void CalculateNextWaypoint(float deltaTime);

	glm::vec3 startPos;
	glm::vec3 startRot;

	glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);
	glm::vec3 LerpWithTime(float currentTime, const glm::vec3& startValue, const glm::vec3& endValue, float totalDuration);
	
	static float EaseIn(float time);
	static float EaseOut(float time);


	glm::vec3 CalculateCubicBezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);






	float easeInTime = 0.0f;
	float easeOutTime = 0.0f;

	float easeInRatio = 0;
	float easeOutRatio = 0;

	float easeInStart = 0;
	float easeOutStart = 0;

	float time = 5;
	float timeStep = 0;
	float lerpValue = 0;
	glm::vec3 m_startPos;

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;

	glm::vec3 Direction = glm::vec3(0, 0, 0);
	glm::vec3 cameraOffset = glm::vec3(0, -2, 3.5f);
	float speed = 20;
};

