#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"

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

	glm::vec3 LerpObject(const glm::vec3& a , const glm::vec3& b, float t);

	template <typename T>
	T LerpWithSpeed(const T& current, const T& target, float speed, float deltaTime) 
	{
		float t = glm::min(speed * deltaTime, 1.0f);
		return LerpObject(current, target, t);
	}

	glm::vec3 cubicBezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;

	glm::vec3 Direction = glm::vec3(0, 0, 0);
	glm::vec3 cameraOffset = glm::vec3(0, -2, 3.5f);
	float speed = 20;
};

