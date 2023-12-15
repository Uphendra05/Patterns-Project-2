#pragma once


#include "model.h"
#include "Command.h"

class MoveAlongAxisWithTime : public Command
{
public:
	MoveAlongAxisWithTime(Model* model, int Axis, float time, float speed);
	~MoveAlongAxisWithTime();

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

private:

	Model* model;

	int axis;

	float time;

	float timeStep;

	float speed;
};

