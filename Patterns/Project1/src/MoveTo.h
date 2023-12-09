#pragma once

#include "model.h"
#include "Command.h"

class MoveTo : public Command
{
public:
	MoveTo();
	MoveTo(Model*& model, const glm::vec3& targetPosition);
	 ~MoveTo();

	void SetModel(Model& model);

	 void Start() override;
	 void Update(float deltatime) override;
	 bool IsComplete() override;

	 glm::vec3 GetModelPosition();

	 glm::vec3 endPosition;
	 glm::vec3 StartPosition;
private:
	
	Model* model;

	bool isAnimationCompleted = false;
};

