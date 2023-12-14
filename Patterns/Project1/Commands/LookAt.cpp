#include "LookAt.h"

LookAt::LookAt(Model* currentTransform, Model* lookAtTransform)
{

	this->currentTransform = currentTransform;
	this->lookAtTransfrom = lookAtTransform;


}

LookAt::LookAt(Transform& cameraTransform, Model* lookAtTransform)
{
	this->cameraTransform = cameraTransform;
	this->lookAtTransfrom = lookAtTransform;

}

LookAt::~LookAt()
{
}

void LookAt::Start()
{


}

void LookAt::Update()
{

	forward = glm::normalize(lookAtTransfrom->transform.position - currentTransform->transform.position);
	right = glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
	up = glm::normalize(glm::cross(forward, right));

	currentTransform->transform.SetOrientationFromDirections(up, -right);

	
}

void LookAt::CameraLookAt()
{

	forward = glm::normalize(lookAtTransfrom->transform.position - cameraTransform.position);
	right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
	up = glm::normalize(glm::cross(forward, right));

	cameraTransform.SetOrientationFromDirections(up, right);




}

void LookAt::End()
{


}
