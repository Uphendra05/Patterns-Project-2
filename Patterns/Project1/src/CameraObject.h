#pragma once
#include "Camera.h"
#include  "GameObject.h"
class CameraObject : public GameObject
{
public:
	CameraObject();
	~CameraObject();

	Camera* camera;
	Transform* GetTransform() override;

private:

};

