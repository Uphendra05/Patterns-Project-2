#pragma once
#include "Command.h"
#include "model.h"

class ScaleTo :public Command
{
public:
	ScaleTo(Model*& model, const glm::vec3& Scale, const float& time);
	~ScaleTo();


	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

	glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);
private:

	Model* model;
	glm::vec3 targetScale;
	float time;

	float timeStep;

	float lerpValue;

	glm::vec3 currentScale;
};

