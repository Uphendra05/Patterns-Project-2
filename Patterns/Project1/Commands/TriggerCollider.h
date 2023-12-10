#pragma once
#include <iostream>
#include "../../src/model.h"
#include "../../src/PhysicsEngine.h"

class TriggerCollider
{

public:
	TriggerCollider(GraphicsRender& render, Shader* shader);
	~TriggerCollider();

	void Start();
	void Update();
	void End();


private:

	Model* m_PlaneModel;
	PhysicsObject* m_PlaneModelPhyObj;
	PhysicsEngine* m_Engine;

	GraphicsRender* m_Renderer;
	Shader* m_Shader;


};

