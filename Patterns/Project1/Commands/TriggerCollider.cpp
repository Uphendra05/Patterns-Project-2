#include "TriggerCollider.h"

TriggerCollider::TriggerCollider(GraphicsRender& render, Shader* shader)
{

	this->m_Renderer = &render;
	this->m_Shader = shader;


}

TriggerCollider::~TriggerCollider()
{
}

void TriggerCollider::Start()
{
	m_PlaneModel = new Model("..");
	m_PlaneModel->id = "Plane";
	m_PlaneModel->transform.SetPosition(glm::vec3(0, 0, 2));
	m_Renderer->AddModelsAndShader(m_PlaneModel, m_Shader);


	m_PlaneModelPhyObj = new PhysicsObject(m_PlaneModel);

	m_PlaneModelPhyObj->Initialize(SPHERE, true, DYNAMIC);
	m_PlaneModelPhyObj->gravityValue = 0;

	m_PlaneModelPhyObj->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	m_Engine->AddPhysicsObjects(m_PlaneModelPhyObj);


}

void TriggerCollider::Update()
{
}

void TriggerCollider::End()
{
}
