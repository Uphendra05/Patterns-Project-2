#pragma once

#include <glm/glm.hpp>
#include "GraphicsRender.h"


struct CubicBezierPoint
{
	glm::vec3 point;
	glm::vec3 controlPoint;
	glm::vec3 rotationOffset;

	CubicBezierPoint(const glm::vec3& point, const glm::vec3& controlPoint, glm::vec3 rotationOffset)
	{
		this->point = point;
		this->controlPoint = controlPoint;
		this->rotationOffset = rotationOffset;
	}

};

struct PointOnCurve
{
	glm::vec3 point;
	glm::vec3 tangent;
	glm::vec3 rotationOffset;

	PointOnCurve(const glm::vec3& point, const glm::vec3& tangent, glm::vec3 rotationOffset)
	{
		this->point = point;
		this->tangent = tangent;
		this->rotationOffset = rotationOffset;
	}
};

static glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}

class CubicBezierCurve
{
public:

	float spacing = 0;

	CubicBezierCurve(float spacing = 0.01f);

	void CalculateCurve();
	void DrawCurve();

	int GetCurveCount();

	void AddPoint(CubicBezierPoint point);

	PointOnCurve GetCachedPointOnCurve(int index);


private:

	GraphicsRender* renderer;
	Shader* shader;
	Model* defaultSphere = nullptr;
	Model* defaultcube = nullptr;

	bool visualize = true;

	std::vector<CubicBezierPoint> listOfPoints;
	std::vector<PointOnCurve> listOfPointsOnCurve;

	PointOnCurve GetPointOnCurve(float t) const;


	std::vector<Model*> listOfDebugSphereModels;
	std::vector<Model*> listOfDebugCubeModels;
};


