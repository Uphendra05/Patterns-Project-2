#pragma once


#include "GameObject.h"
#include "Command.h"

class SpawnObject :public Command
{
public:
	SpawnObject(GameObject* gameObject, float time);
	~SpawnObject();

	SpawnObject(Model* model);

	void LoadModel();

	void Start() override;
	void Update(float deltatime) override;
	void SetStarted(bool isStarted) override;

	bool IsComplete() override;
	bool IsStarted() override;

private:

	Model* model;

	GameObject* gameObject;

	float time;
	float timeStep;

};

