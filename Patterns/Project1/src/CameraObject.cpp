#include "CameraObject.h"
#include "Singleton.h"

CameraObject::CameraObject()
{
	camera = Singleton::GetInstance().GetCamera();
	Singleton::GetInstance().AddGameObject(this);
	SetGameObjectId("CAMERA");

}

CameraObject::~CameraObject()
{
}

Transform* CameraObject::GetTransform()
{
	return &camera->transform;
}
