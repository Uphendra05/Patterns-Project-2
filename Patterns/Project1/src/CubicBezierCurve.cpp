#include "CubicBezierCurve.h"
#include "Singleton.h"


CubicBezierCurve::CubicBezierCurve(float spacing)
{
	this->renderer = Singleton::GetInstance().GetRenderer();
	this->shader = Singleton::GetInstance().GetDefaultShader();

	this->spacing = spacing;

	this->defaultSphere = Singleton::GetInstance().GetDefaultSphere();
	this->defaultcube = Singleton::GetInstance().GetDefaultCube();
}

void CubicBezierCurve::CalculateCurve()
{
	listOfPointsOnCurve.clear();

	listOfDebugSphereModels.clear();

	int count = 1 / spacing;

	for (int i = 0; i <= count; i++)
	{
		listOfPointsOnCurve.push_back(GetPointOnCurve(i * spacing));
	}

	for (PointOnCurve point : listOfPointsOnCurve)
	{
		Model* sphere = new Model(*defaultSphere);

		sphere->transform.SetPosition(point.point);
		sphere->transform.SetScale(glm::vec3(0.2f));

		//renderer->AddModelsAndShader(sphere, shader);

		listOfDebugSphereModels.push_back(sphere);

	}


}


void CubicBezierCurve::DrawCurve()
{
	if (!visualize) return;

	for (Model* model : listOfDebugSphereModels)
	{
		//Model* sphere = new Model(*defaultSphere);

		//sphere->transform.SetPosition(point.point);
		//sphere->transform.SetScale(glm::vec3(0.2f));
		model->Draw(*shader);

		//renderer->DrawSphere(point.point, 0.1f, glm::vec4(1, 0, 0, 1));
	}

	
	for (Model* model : listOfDebugCubeModels)
	{
		//Model* sphere = new Model(*defaultSphere);

		//sphere->transform.SetPosition(point.point);
		//sphere->transform.SetScale(glm::vec3(0.2f));
		model->Draw(*shader);

		//renderer->DrawSphere(point.point, 0.1f, glm::vec4(1, 0, 0, 1));
	}


	//for (CubicBezierPoint point : listOfPoints)
	//{
	//	//renderer->DrawSphere(point.point, 0.1f, glm::vec4(0, 1, 0, 1));
	////	renderer->DrawSphere(point.point, 0.1f, glm::vec4(00, 0, 1, 1));
	//}
}


int CubicBezierCurve::GetCurveCount()
{
	return listOfPointsOnCurve.size();
}

void CubicBezierCurve::AddPoint(CubicBezierPoint point)
{
	listOfPoints.push_back(point);



	Model* cube = new Model(*defaultcube);

	cube->transform.SetScale(glm::vec3(0.2f));
	//renderer->AddModelsAndShader(cube, shader);

	listOfDebugCubeModels.push_back(cube);

}

PointOnCurve CubicBezierCurve::GetCachedPointOnCurve(int index)
{
	return listOfPointsOnCurve[index];
}



PointOnCurve CubicBezierCurve::GetPointOnCurve(float time) const
{
	int startIndex;
	int endIndex;

	if (time == 1)
	{
		return PointOnCurve(listOfPoints[listOfPoints.size() - 1].point, glm::vec3(0), glm::vec3(0));
	}

	float segment = 1.0f / (listOfPoints.size() - 1);


	startIndex = std::floor(time / segment);
	endIndex = startIndex + 1;

	float t = (time - startIndex * segment) / segment;


	/*Debugger::Print("StartIndex :", startIndex);
	Debugger::Print("EndIndex :", endIndex);
	Debugger::Print("Time :", time);
	Debugger::Print("T :", t);*/

	CubicBezierPoint point1 = listOfPoints[startIndex];
	CubicBezierPoint point2 = listOfPoints[endIndex];

	glm::vec3 rotation = Lerp(point1.rotationOffset, point2.rotationOffset, t);

	glm::vec3 point1Control = point1.controlPoint;

	if (startIndex != 0)
	{
		glm::vec3 diff = point1.point - point1.controlPoint;


		point1Control = point1.point + diff;
	}

	float x, y, z;

	x = std::pow((1 - t), 3) * point1.point.x + 3 * std::pow((1 - t), 2) * t * point1Control.x +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.x + std::pow(t, 3) * point2.point.x;

	y = std::pow((1 - t), 3) * point1.point.y + 3 * std::pow((1 - t), 2) * t * point1Control.y +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.y + std::pow(t, 3) * point2.point.y;

	z = std::pow((1 - t), 3) * point1.point.z + 3 * std::pow((1 - t), 2) * t * point1Control.z +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.z + std::pow(t, 3) * point2.point.z;

	return PointOnCurve(glm::vec3(x, y, z), glm::vec3(0), rotation);
}


