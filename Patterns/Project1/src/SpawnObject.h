#pragma once
#include "model.h"
#include "GraphicsRender.h"

#include "Command.h"
class SpawnObject :public Command
{
public:
	SpawnObject();
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
};

