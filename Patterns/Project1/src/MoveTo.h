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
	 void SetStarted(bool isStarted) override;

	 bool IsComplete() override;
	 bool IsStarted() override;


	 glm::vec3 GetModelPosition();

	 glm::vec3 endPosition;
	 glm::vec3 StartPosition;
private:
	
	Model* model;

	bool isAnimationCompleted = false;
};

