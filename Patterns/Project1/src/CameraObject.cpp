#include "CameraObject.h"
#include "Singleton.h"

CameraObject::CameraObject()
{
	camera = Singleton::GetInstance().GetCamera();

	SetGameObjectId("CAMERA");
}

CameraObject::~CameraObject()
{
}

Transform* CameraObject::GetTransform()
{
	return camera->GetTransform();
}
