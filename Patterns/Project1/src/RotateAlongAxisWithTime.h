#pragma once
#include "Command.h"
#include "model.h"

class RotateAlongAxisWithTime : public  Command
{
public:
	RotateAlongAxisWithTime(Model* model, int Axis, float time, float speed);
	~RotateAlongAxisWithTime();

	

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

private:

	Model* model;
	int rotationAxis;
	float time;
	float timeStep;
	float speed;
};

